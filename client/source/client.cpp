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
		ClientDataType clientDataType = _dataFromServer.clientDataType();

		qDebug() << "message = " << _dataFromServer.textMessageData().first;
		qDebug() << "sender = " << _dataFromServer.userName();
		qDebug() << "DataType = " << static_cast<int>(_dataFromServer.clientDataType());

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

	clientData.setUserName(_username);
	clientData.setTextMessageData({text, clientData.userName()});
	clientData.setClientDataType(ClientDataType::MessageType);
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
	qDebug() << "type = " << static_cast<int>(type);
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
		case ClientDataType::Undefined:
		{
			break;
		}
	}
}
