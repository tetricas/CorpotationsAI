#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "game_space.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<CGameSpace>("game_space", 1, 0, "GameSpace");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
