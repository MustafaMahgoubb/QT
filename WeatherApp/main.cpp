#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <weathermanager.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    WeatherManager appManager;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("weatherManager", &appManager);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WeatherApp", "Main");

    return app.exec();
}
