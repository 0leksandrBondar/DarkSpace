#include "clientdata.h"

#include <QDataStream>
#include <QDebug>

std::pair<QString, QString> ClientData::textMessageData() const
{
	return _textMessageData;
}

void ClientData::setTextMessageData(const std::pair<QString, QString>& newTextMessageData)
{
	_textMessageData = newTextMessageData;
}

std::pair<QString, QString> ClientData::signInData() const
{
	return _signInData;
}

ClientDataType ClientData::clientDataType() const
{
	return _clientDataType;
}

void ClientData::setSignInData(const std::pair<QString, QString>& newSignInData)
{
	_signInData = newSignInData;
}

QString ClientData::userName() const
{
	return _userName;
}

void ClientData::setUserName(const QString& newUserName)
{
	_userName = newUserName;
}

QDataStream& operator<<(QDataStream& out, const ClientData& data)
{
	out << data._userName;
	out << data._singUpRequestStatus;
	out << data._singInRequestStatus;
	out << data._signUpData.first;
	out << data._signUpData.second;
	out << data._signInData.first;
	out << data._signInData.second;
	out << data._textMessageData.first;
	out << data._textMessageData.second;
	out << data._clientDataType;

	return out;
}

QDataStream& operator>>(QDataStream& in, ClientData& data)
{
	in >> data._userName;
	in >> data._singUpRequestStatus;
	in >> data._singInRequestStatus;
	in >> data._signUpData.first;
	in >> data._signUpData.second;
	in >> data._signInData.first;
	in >> data._signInData.second;
	in >> data._textMessageData.first;
	in >> data._textMessageData.second;
	in >> data._clientDataType;

	return in;
}

void ClientData::setClientDataType(const ClientDataType dataType)
{
	_clientDataType = dataType;
}

void ClientData::setSignUpData(const std::pair<QString, QString>& newSignInData)
{
	_signUpData = newSignInData;
}

bool ClientData::isSingUpRequestSuccessful() const
{
	return _singUpRequestStatus;
}

bool ClientData::isSingInRequestSuccessful() const
{
	return _singInRequestStatus;
}

void ClientData::setSignUpRequestStatus(bool status)
{
	_singUpRequestStatus = status;
}

void ClientData::setSignInRequestStatus(bool status)
{
	_singInRequestStatus = status;
}

std::pair<QString, QString> ClientData::signUpData() const
{
	return _signUpData;
}
