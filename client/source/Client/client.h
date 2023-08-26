#pragma once

#include "ClientData/clientdata.h"

#include <QObject>

class QTcpSocket;

class Client : public QObject
{
	Q_OBJECT
public:
	Client();

	void onRedyRead();

signals:
	void getMessageFromServer(const QString& data, const QString& username);

public slots:
	[[nodiscard]] QString username() const;
	void setUsername(const QString& newUsername);

	void sendMessageData(const QString& text);
	void sendMessageDataToServer(ClientData& messageData);
	void sendSignInData(const QString& login, const QString& password);
	void sendSignUpData(const QString& login, const QString& password);

	// ----- init message data from UI

	void fillMessageData(const QString& text);

private:
	QString _username;
	QTcpSocket* _socket;
	ClientData _messageData;
};
