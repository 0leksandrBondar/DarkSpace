#include "dbmanager.h"
#include "ClientData/clientdata.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>



DBManager::DBManager(QObject* parent)
{
}

bool DBManager::addClientToDataBase(const ClientData& data)
{
	QSqlQuery insertQuery(*_db);

	const QString login = data.signInData().first;
	const QString password = data.signInData().second;
	const QString userName = data.userName();

	const bool clientExist = isUserExistInDataBase(login);

	if (clientExist)
	{
		return true;
	}

	insertQuery.prepare(
		QStringLiteral("INSERT INTO Clients (Login, Password, UserName) VALUES (:login, :password, "
					   ":userName)"));
	insertQuery.bindValue(QStringLiteral(":login"), login);
	insertQuery.bindValue(QStringLiteral(":password"), password);
	insertQuery.bindValue(QStringLiteral(":userName"), userName);

	if (!insertQuery.exec())
	{
		qWarning() << "Error adding user to database:" << insertQuery.lastError().text();
	}
	return true;
}

bool DBManager::isUserExistInDataBase(const QString& login)
{
	QSqlQuery checkQuery(*_db);

	checkQuery.prepare(QStringLiteral("SELECT COUNT(*) FROM Clients WHERE Login = :login"));
	checkQuery.bindValue(QStringLiteral(":login"), login);

	if (checkQuery.exec() && checkQuery.next())
	{
		int userCount = checkQuery.value(0).toInt();
		if (userCount > 0)
		{
			qWarning() << "User with login" << login << "already exists.";
			return true;
		}
	}
	else
	{
		qWarning() << "Error checking user existence:" << checkQuery.lastError().text();
		return false;
	}
	return false;
}
