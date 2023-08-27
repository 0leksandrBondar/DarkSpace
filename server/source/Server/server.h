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
	~Server();

private:
	void onReadyRead();
	void sendToClient(const ClientData* data);
	void incomingConnection(qintptr socketDescriptor) override;

private:
	//  ------- processing data from client
	void processingClientDataFromClient();

	void processingSingInType();
	void processingSingUpType();
	void processingMessageType();

private:
	DBManager* _db;
	QByteArray _data;
	QTcpSocket* _socket;
	ClientData* _dataFromClient;
	QVector<QTcpSocket*> _sockets;
};
