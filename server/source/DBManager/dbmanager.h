#pragma once

#include <QObject>
#include <QSqlDatabase>

class ClientData;

class DBManager : public QObject
{
	Q_OBJECT
public:
	explicit DBManager(QObject* parent = nullptr);

	bool addClientToDataBase(const ClientData* data);
	bool isUserExistInDataBase(const QString& login);

private:
	std::unique_ptr<QSqlDatabase> _db;
};
