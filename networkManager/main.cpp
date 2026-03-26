#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "wifimanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    WifiManager manager;

    // Expose to QML


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("wifiManager", &manager);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("networkManager", "Main");

    return app.exec();
}
