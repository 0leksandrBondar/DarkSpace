#include "server.h"

#include "dbmanager.h"

#include <QDebug>
#include <QTcpSocket>

Server::Server() : _db{ new DBManager(this) }, _dataFromClient{ new ClientData }
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
    delete _db;
    delete _senderSocket;
    delete _dataFromClient;
}

/*!
 * \brief Server::onReadyRead this method is called when any client sends information to the server
 * and processes it.
 */
void Server::onReadyRead()
{
    _senderSocket = dynamic_cast<QTcpSocket*>(sender());

    QDataStream input(_senderSocket);

    if (input.status() != QDataStream::Ok)
    {
        return;
    }

    input >> *_dataFromClient;

    socketIdentificationDuringAuth();
    processingClientDataFromClient();
}

/*!
 * \brief Server::receiverSocket this method handles information about which client should receive
 * the information. \return a specific socket that should receive information.
 */
QTcpSocket* Server::receiverSocket()
{
	const bool isSearchType {_dataFromClient->clientDataType() == ClientDataType::SearchUser};
	const bool isMessageType {_dataFromClient->clientDataType() == ClientDataType::MessageType};
	const bool isAuthType {_dataFromClient->clientDataType() == ClientDataType::SignInType ||
						   _dataFromClient->clientDataType() == ClientDataType::SignUpType};

	for (const auto* connectedSocket : std::as_const(_sockets))
	{
		const bool isDifferentSocket {connectedSocket->_socket != _senderSocket};
		const bool isSameClientSender {connectedSocket->_socket == _senderSocket};
		const bool isMatchingReceiver {connectedSocket->_userName == _dataFromClient->receiver()};

		if ((isSameClientSender && (isAuthType || isSearchType)) || (isDifferentSocket && isMatchingReceiver && isMessageType))
		{
			return connectedSocket->_socket;
		}
	}
	return nullptr;
}

/*!
 * \brief Server::sendToClient sends information to a specific socket.
 */
void Server::sendToClient(const ClientData* data)
{
    _data.clear();
    QDataStream output(&_data, QIODevice::WriteOnly);
    output << *data;

    auto* socket = receiverSocket();

    if (socket != nullptr)
    {
        socket->write(_data);
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    _senderSocket = new QTcpSocket(this);
    _senderSocket->setSocketDescriptor(socketDescriptor);
    connect(_senderSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(_senderSocket, &QTcpSocket::disconnected, this, &Server::onDisconnected);
    _sockets.push_back(new ClientInfo{ "", _senderSocket });

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

/*!
 * \brief Server::processingMessageType sends a message of type ClientDataType::MessageType to some
 * client
 */
void Server::processingMessageType() { sendToClient(_dataFromClient); }

/*!
 * \brief Server::processingSingUpType adds a new user to the database if it does not exist
 */
void Server::processingSingUpType()
{
    const bool isClientAdded = _db->addClientToDataBase(_dataFromClient);
    _dataFromClient->setSignUpRequestStatus(isClientAdded);
    sendToClient(_dataFromClient);
}

/*!
 * \brief Server::processingSingInType this method checks if a client with the provided login exists
 * in the server's database and responds with the result.
 */
void Server::processingSingInType()
{
    const QString login = _dataFromClient->signInData().first;
    const bool isClientExist = _db->isUserExistInDataBase(login);

    _dataFromClient->setSignInRequestStatus(isClientExist);
    sendToClient(_dataFromClient);
}

/*!
 * \brief Server::socketIdentificationDuringAuth identifies all new connections by the username
 * entered by the client during authentication
 */
void Server::socketIdentificationDuringAuth()
{
    const bool isAuthType{ _dataFromClient->clientDataType() == ClientDataType::SignInType
                           || _dataFromClient->clientDataType() == ClientDataType::SignUpType };

    if (isAuthType)
    {
        for (auto* connectedSocket : _sockets)
        {
            const bool isSameClientSender{ connectedSocket->_socket == _senderSocket };

            if (isSameClientSender)
            {
                connectedSocket->_userName = _dataFromClient->userName();
            }
        }
    }
}

void Server::processingSearchType()
{
    const auto it = std::find_if(_sockets.cbegin(), _sockets.cend(),
                                 [this](ClientInfo* socket)
                                 { return socket->_userName == _dataFromClient->receiver(); });

    _dataFromClient->setSearchUserResult(it != _sockets.cend());
    sendToClient(_dataFromClient);
}

void Server::onDisconnected()
{
    auto* disconnectedSocket = dynamic_cast<QTcpSocket*>(sender());
    if (disconnectedSocket)
    {
        for (auto it = _sockets.begin(); it != _sockets.end(); ++it)
        {
            if ((*it)->_socket == disconnectedSocket)
            {
                qDebug() << "Client disconnected: " << disconnectedSocket->socketDescriptor();
                _sockets.erase(it);
                break;
            }
        }
    }
    _senderSocket->deleteLater();
}
