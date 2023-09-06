#include "server.h"

#include "dbmanager.h"

#include <QDebug>
#include <QTcpSocket>

Server::Server() : _db{new DBManager(this)}, _dataFromClient{new ClientData}
{
	if (listen(QHostAddress::AnyIPv4, 2023))
	{
		qDebug() << "Server start listening";
	}
	else
	{
		qDebug() << "Server doesn't start listen";
	}
}

Server::~Server()
{
	delete _dataFromClient;
}

void Server::onReadyRead()
{
	_client->_socket = (QTcpSocket*) sender();
	QDataStream input(_client->_socket);

	if (input.status() != QDataStream::Ok)
	{
		return;
	}

	input >> *_dataFromClient;

	socketIdentification();
	processingClientDataFromClient();
}

void Server::sendToClient(const ClientData* data)
{
	_data.clear();
	QDataStream output(&_data, QIODevice::WriteOnly);
	output << *data;

	for (auto* socket : qAsConst(_sockets))
	{
		// TODO: optimize it
		if (socket->_socket == _client->_socket && _dataFromClient->clientDataType() != ClientDataType::MessageType)
		{
			socket->_socket->write(_data);
		}

		// TODO: instead of "Oleksandr" use custom username
		if (socket->_socket != _client->_socket && socket->_userName == "Oleksandr" &&
			_dataFromClient->clientDataType() == ClientDataType::MessageType)
		{
			qDebug() << "send message to client (only for Oleksandr)";
			socket->_socket->write(_data);
		}
	}
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	_client = new ClientSocket;
	_client->_socket = new QTcpSocket(this);
	_client->_socket->setSocketDescriptor(socketDescriptor);
	connect(_client->_socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
	connect(_client->_socket, &QTcpSocket::disconnected, _client->_socket, &QTcpSocket::deleteLater);
	_sockets.push_back(_client);

	qDebug() << "client is connected to server = " << socketDescriptor;
}

void Server::processingClientDataFromClient()
{
	const auto clientDataType = static_cast<ClientDataType>(_dataFromClient->clientDataType());

	switch (clientDataType)
	{
		case ClientDataType::MessageType:
		{
			processingMessageType();
			break;
		}
		case ClientDataType::SignUpType:
		{
			processingSingUpType();
			break;
		}
		case ClientDataType::SignInType:
		{
			processingSingInType();
			break;
		}
		case ClientDataType::SearchUser:
		{
			processingSearchType();
			break;
		}
		case ClientDataType::Undefined:
		{
			break;
		}
	}
}

void Server::processingMessageType()
{
	sendToClient(_dataFromClient);
}

void Server::processingSingUpType()
{
	const bool isClientAdded = _db->addClientToDataBase(_dataFromClient);
	_dataFromClient->setSignUpRequestStatus(isClientAdded);
	sendToClient(_dataFromClient);
}

void Server::processingSingInType()
{
	const QString login = _dataFromClient->signInData().first;
	const bool isClientExist = _db->isUserExistInDataBase(login);

	_dataFromClient->setSignInRequestStatus(isClientExist);
	sendToClient(_dataFromClient);
}

void Server::socketIdentification()
{
	if (_dataFromClient->clientDataType() == ClientDataType::SignUpType ||
		_dataFromClient->clientDataType() == ClientDataType::SignInType)
	{
		for (auto* connectedSocket : _sockets)
		{
			if (connectedSocket->_socket == _client->_socket)
			{
				connectedSocket->_userName = _dataFromClient->userName();
			}
		}
	}
}

void Server::processingSearchType()
{
	const auto it = std::find_if(_sockets.begin(), _sockets.end(),
		[this](ClientSocket* socket) { return socket->_userName == _dataFromClient->receiver(); });

	_dataFromClient->setSearchUserResult(it != nullptr);

	qDebug() << "Server =  Search User result = " << (it != nullptr);
	sendToClient(_dataFromClient);
}
