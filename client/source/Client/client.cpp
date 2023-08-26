#include "client.h"

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
		input >> _messageData;
		emit getMessageFromServer(_messageData.textMessageData().first, _messageData.userName());
	}
}

void Client::sendMessageDataToServer(ClientData& messageData)
{
	QByteArray data;
	QDataStream output(&data, QIODevice::WriteOnly);

	messageData.setClientDataType(ClientDataType::MessageType);

	output << messageData;

	_socket->write(data);
}

void Client::sendSignInData(const QString& login, const QString& password)
{
	ClientData data;

	data.setUserName(_username);
	data.setSignInData({login, password});
	data.setClientDataType(ClientDataType::SignInType);
	sendMessageDataToServer(data);
}

void Client::sendSignUpData(const QString& login, const QString& password)
{
	_messageData.setClientDataType(ClientDataType::SignUpType);
}

void Client::fillMessageData(const QString& text)
{
	QByteArray data;
	QDataStream output(&data, QIODevice::WriteOnly);

	_messageData.setUserName(_username);
	_messageData.setTextMessageData({text, _username});
	_messageData.setClientDataType(ClientDataType::MessageType);
	output << _messageData;

	_socket->write(data);
}

void Client::sendMessageData(const QString& text)
{
}

QString Client::username() const
{
	return _username;
}

void Client::setUsername(const QString& newUsername)
{
	_username = newUsername;
}
