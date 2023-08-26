#include "server.h"

#include "dbmanager.h"
#include "ClientData/clientdata.h"

#include <QDebug>
#include <QTcpSocket>

Server::Server() : _db{new DBManager(this)}, _socket{new QTcpSocket(this)}
{
	if (listen(QHostAddress::AnyIPv4, 2023))
	{
		qDebug() << "Server start listening";
	}
	else
	{
		qDebug() << "Server does't start listen";
	}
}

void Server::onReadyRead()
{
	_socket = (QTcpSocket*) sender();
	QDataStream input(_socket);

	if (input.status() == QDataStream::Ok)
	{
		ClientData dataFromClient;

		input >> dataFromClient;

		if (dataFromClient.clientDataType() == ClientDataType::MessageType)
		{
			qDebug() << "client message " << dataFromClient.textMessageData().first << " " << dataFromClient.userName();
			sendToClient(dataFromClient);
		}
	}
	else
	{
		qDebug() << "Server read Error";
	}
}

void Server::sendToClient(const ClientData& data)
{
	_data.clear();
	QDataStream output(&_data, QIODevice::WriteOnly);
	output << data;

	for (auto* socket : qAsConst(_sockets))
	{
		if (socket != _socket)
		{
			socket->write(_data);
		}
	}
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	_socket = new QTcpSocket(this);
	_socket->setSocketDescriptor(socketDescriptor);
	connect(_socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
	connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);
	_sockets.push_back(_socket);

	qDebug() << "client is connected to server = " << socketDescriptor;
}
