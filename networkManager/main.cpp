#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "wifimanager.h"
#include "bluetoothManager.h"
#include "BluetoothDevice.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register BluetoothDevice for QML
    qRegisterMetaType<BluetoothDevice>("BluetoothDevice");
    qRegisterMetaType<QList<BluetoothDevice>>("QList<BluetoothDevice>");

    WifiManager manager;
    bluetoothManager btManager;

    // Expose to QML


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("wifiManager", &manager);
    engine.rootContext()->setContextProperty("bluetoothManager", &btManager);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("networkManager", "Main");

    return app.exec();
}
