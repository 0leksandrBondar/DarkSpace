#include "client.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;

	qmlRegisterType<Client>("ClientSide", 1, 0, "Client");

	engine.load(QUrl(QStringLiteral("qrc:/main_gui.qml")));

	return app.exec();
}
