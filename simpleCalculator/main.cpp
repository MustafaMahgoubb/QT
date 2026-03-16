#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Create Calculator Object
    Calculator calculator;


    QQmlApplicationEngine engine;

    // Expose the Calculator object to QML as "calc"
    engine.rootContext()->setContextProperty("calc", &calculator);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("simpleCalculator", "Main");

    return app.exec();
}
