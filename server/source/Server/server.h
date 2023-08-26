#pragma once

#include "ClientData/clientdata.h"

#include <QTcpServer>

class QTcpSocket;

class DBManager;

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();

private:
	void onReadyRead();
	void sendToClient(const ClientData& data);
	void incomingConnection(qintptr socketDescriptor) override;

private:
	DBManager* _db;
	QByteArray _data;
	QTcpSocket* _socket;
	QVector<QTcpSocket*> _sockets;
};
