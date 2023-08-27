#include "dbmanager.h"

#include "ClientData/clientdata.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

DBManager::DBManager(QObject* parent) : _db{new QSqlDatabase(QSqlDatabase::addDatabase(QStringLiteral("QSQLITE")))}
{
	_db->setDatabaseName(QStringLiteral("dataBase.db"));
	QSqlQuery query(*_db);

	if (!_db->open())
	{
		qWarning() << QStringLiteral("Database not open. Error: ") << _db->lastError().text();
	}
	else
	{
		query.exec(
			QStringLiteral("CREATE TABLE IF NOT EXISTS Clients (id INTEGER PRIMARY KEY, Login, password TEXT"
						   "TEXT, userName TEXT)"));
	}
}

bool DBManager::addClientToDataBase(const ClientData* data)
{
	QSqlQuery insertQuery(*_db);

	const QString login = data->signUpData().first;
	const QString password = data->signUpData().second;
	const QString userName = data->userName();

	const bool clientExist = isUserExistInDataBase(userName);

	if (clientExist)
	{
		return false;
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
