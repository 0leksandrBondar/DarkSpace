#pragma once

#include <QString>

enum class ClientDataType
{
	Undefined = -1,
	MessageType,
	SignInType,
	SignUpType
};

class ClientData
{
public:
	ClientData() = default;

	friend QDataStream& operator>>(QDataStream& in, ClientData& data);
	friend QDataStream& operator<<(QDataStream& out, const ClientData& data);

	[[nodiscard]] QString userName() const;
	[[nodiscard]] ClientDataType clientDataType() const;
	[[nodiscard]] std::pair<QString, QString> signInData() const;
	[[nodiscard]] std::pair<QString, QString> textMessageData() const;

	void setUserName(const QString& newUsername);
	void setClientDataType(ClientDataType dataType);
	void setSignInData(const std::pair<QString, QString>& newSignInData);
	void setTextMessageData(const std::pair<QString, QString>& newTextMessageData);

private:
	QString _userName;

	std::pair<QString, QString> _signUpData;
	std::pair<QString, QString> _signInData;
	std::pair<QString, QString> _textMessageData;

	ClientDataType _clientDataType{ClientDataType::Undefined};
};
