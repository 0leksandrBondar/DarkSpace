#pragma once

#include "ClientData/clientdata.h"

#include <QString>
#include <QTcpServer>

#include <vector>

class QTcpSocket;
class DBManager;

struct ClientInfo
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
	QTcpSocket* receiverSocket();
	void socketIdentificationDuringAuth();
	void sendToClient(const ClientData* data);
	void incomingConnection(qintptr socketDescriptor) override;

private:
	//  ------- processing data from client
	void processingClientDataFromClient();

	void processingSingInType();
	void processingSearchType();
	void processingSingUpType();
	void processingMessageType();

private:
	DBManager* _db;
	QByteArray _data;
	QTcpSocket* _senderSocket;
	ClientData* _dataFromClient;
	std::vector<ClientInfo*> _sockets;
};
