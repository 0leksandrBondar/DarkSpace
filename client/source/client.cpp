#include "client.h"

#include <QDebug>
#include <QTcpSocket>

Client::Client() : _socket{new QTcpSocket(this)}
{
	_socket->connectToHost(QStringLiteral("192.168.3.28"), 2023);
	connect(_socket, &QTcpSocket::readyRead, this, &Client::onRedyRead);
	connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);
	connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);
}

void Client::onRedyRead()
{
	QDataStream input(_socket);
	if (input.status() == QDataStream::Ok)
	{
		input >> _dataFromServer;
		const ClientDataType clientDataType = _dataFromServer.clientDataType();
		processingClientDataFromServer(clientDataType);
	}
}

void Client::fillSignInData(const QString& login, const QString& password)
{
	ClientData data;

	data.setUserName(_username);
	data.setSignInData({login, password});
	data.setClientDataType(ClientDataType::SignInType);

	sendClientDataToServer(data);
}

void Client::fillSignUpData(const QString& login, const QString& password, const QString& userName)
{
	ClientData clientData;

	clientData.setUserName(userName);
	clientData.setClientDataType(ClientDataType::SignUpType);
	clientData.setSignUpData({login, password});

	sendClientDataToServer(clientData);
}

void Client::fillMessageData(const QString& text)
{
	ClientData clientData;

	clientData.setReceiver(_receiver);
	clientData.setUserName(_username);
	clientData.setClientDataType(ClientDataType::MessageType);
	clientData.setTextMessageData({text, clientData.userName()});

	sendClientDataToServer(clientData);
}

void Client::sendClientDataToServer(const ClientData& data)
{
	QByteArray byteArray;
	QDataStream output(&byteArray, QIODevice::WriteOnly);
	output << data;

	_socket->write(byteArray);
}

void Client::setUsername(const QString& newUsername)
{
	_username = newUsername;
}

void Client::processingClientDataFromServer(ClientDataType type)
{
	switch (type)
	{
		case ClientDataType::MessageType:
		{
			emit getMessageFromServer(_dataFromServer.textMessageData().first, _dataFromServer.userName());
			break;
		}
		case ClientDataType::SignUpType:
		{
			emit recivedSignUpRequestStatus(_dataFromServer.isSingUpRequestSuccessful());
			break;
		}
		case ClientDataType::SignInType:
		{
			emit recivedSignInRequestStatus(_dataFromServer.isSingInRequestSuccessful());
			break;
		}
		case ClientDataType::SearchUser:
		{
			if (_dataFromServer.isUserFound() && !isReceiverExist(_dataFromServer.receiver()))
			{
				_listOfOwnChats.push_back(_dataFromServer.receiver());
				emit userIsConnectedToServer(_dataFromServer.receiver());
			}
			break;
		}
		case ClientDataType::Undefined:
		{
			break;
		}
	}
}

void Client::searchUser(const QString& userName)
{
	ClientData clientData;

	qDebug() << "search user = " << userName;
	clientData.setReceiver(userName);
	clientData.setClientDataType(ClientDataType::SearchUser);

	sendClientDataToServer(clientData);
}

QString Client::userName() const
{
	return _username;
}

bool Client::isReceiverExist(const QString& receiver) const
{
	const auto it = std::find(_listOfOwnChats.begin(), _listOfOwnChats.end(), receiver);

	if (it != _listOfOwnChats.end())
	{
		return true;
	}

	return false;
}

void Client::setReceiver(const QString& receiver)
{
	_receiver = receiver;
}
