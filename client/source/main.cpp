#include "client.h"

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	app.setWindowIcon(QIcon(":/AppIcons/icon.ico"));

	qmlRegisterType<Client>("ClientSide", 1, 0, "Client");

	engine.load(QUrl(QStringLiteral("qrc:/main_gui.qml")));

	return app.exec();
}
