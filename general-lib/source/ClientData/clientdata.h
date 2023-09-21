#pragma once

#include <QString>

enum class ClientDataType : int
{
	Undefined = -1,
	MessageType,
	SignInType,
	SignUpType,
	SearchUser
};

class ClientData
{
public:
	ClientData() = default;

	friend QDataStream& operator>>(QDataStream& in, ClientData& data);
	friend QDataStream& operator<<(QDataStream& out, const ClientData& data);

	[[nodiscard]] QString receiver() const;
	[[nodiscard]] QString userName() const;
	[[nodiscard]] bool isUserFound() const;
	[[nodiscard]] ClientDataType clientDataType() const;
	[[nodiscard]] bool isSingUpRequestSuccessful() const;
	[[nodiscard]] bool isSingInRequestSuccessful() const;
	[[nodiscard]] std::pair<QString, QString> signInData() const;
	[[nodiscard]] std::pair<QString, QString> signUpData() const;
	[[nodiscard]] std::pair<QString, QString> textMessageData() const;

	void setSignUpRequestStatus(bool status);
	void setSignInRequestStatus(bool status);

	void setReceiver(const QString& receiver);
	void setSearchUserResult(bool searchResult);
	void setUserName(const QString& newUsername);
	void setClientDataType(ClientDataType dataType);
	void setSignUpData(const std::pair<QString, QString>& newSignInData);
	void setSignInData(const std::pair<QString, QString>& newSignInData);
	void setTextMessageData(const std::pair<QString, QString>& newTextMessageData);

private:
	QString _receiver;
	QString _userName;

	bool _searchUserResult{false};
	bool _singUpRequestStatus{false};
	bool _singInRequestStatus{false};

	std::pair<QString, QString> _signUpData;
	std::pair<QString, QString> _signInData;
	std::pair<QString, QString> _textMessageData;

	ClientDataType _clientDataType{ClientDataType::Undefined};
};
