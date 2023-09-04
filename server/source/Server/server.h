#pragma once

#include "ClientData/clientdata.h"

#include <QString>
#include <QTcpServer>

class QTcpSocket;
class DBManager;

struct ClientSocket
{
	QString _userName;
	QTcpSocket* _socket;
};

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();
	~Server();

private:
	void onReadyRead();
	void socketIdentification();
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
	ClientSocket* _client;
	ClientData* _dataFromClient;
	QVector<ClientSocket*> _sockets;
};
