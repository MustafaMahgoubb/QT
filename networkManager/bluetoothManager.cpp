#include "bluetoothManager.h"
#include <QDBusConnection>
#include <QDBusInterface>
#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusArgument>
#include <QTimer>
#include "BluetoothDevice.h"
#include <QRegularExpression>



bluetoothManager::bluetoothManager(QObject *parent) : QObject{parent}
{
    m_bluetoothAdapterInterface = new QDBusInterface ("org.bluez",
                                                     "/org/bluez/hci0",
                                                     "org.bluez.Adapter1",
                                                     QDBusConnection::systemBus(),
                                                     this);

    if (m_bluetoothAdapterInterface -> isValid())
    {
        qDebug() << "Connected To bluetooth Adapter";
    }
    else
    {
        qDebug() << "Failed to connect to bluetooth Adapter";
    }

    // Create and register agent
    m_agent = new BluetoothAgent(this);

    connect(m_agent, &BluetoothAgent::pairingRequested,
            this, [](const QString &path, quint32 passkey) {
                qDebug() << "Pairing requested:" << path << passkey;
            });

    connect(m_agent, &BluetoothAgent::pairingComplete,
            this, [](bool success) {
                qDebug() << "Pairing complete:" << success;
            });

    m_agent->registerAgent();
}

bluetoothManager::~bluetoothManager() = default;

bool bluetoothManager::isEnabled()
{
    bool state = m_bluetoothAdapterInterface-> property("Powered").toBool();
    return state;
}

bool bluetoothManager::enable()
{
    bool retstate = m_bluetoothAdapterInterface->setProperty("Powered" , true)\
                    && m_bluetoothAdapterInterface->setProperty("Discoverable" , true);

    return retstate;
}

bool bluetoothManager::disable()
{
    bool state = m_bluetoothAdapterInterface->setProperty("Powered" , false);

    return state;
}

void bluetoothManager::scan()
{

    if (m_bluetoothAdapterInterface -> isValid())
    {
        qDebug() << "bluetooth Adapter is Available";
    }
    else
    {
        qDebug() << "bluetooth Adapter isn't Available";
        return;
    }

    m_bluetoothAdapterInterface->call("StartDiscovery");

    QTimer::singleShot(3000, this, [this]() {
        m_bluetoothAdapterInterface->call("StopDiscovery");
        qDebug() << "Scan stopped";
        emit devicesFound(getDevices());
    });
}

QList<BluetoothDevice> bluetoothManager::getDevices()
{
    QList<BluetoothDevice> deviceList;

    // Get list of device paths using Introspect
    QDBusInterface introspect(
        "org.bluez",
        "/org/bluez/hci0",
        "org.freedesktop.DBus.Introspectable",
        QDBusConnection::systemBus()
        );

    if (!introspect.isValid()) {
        qDebug() << "Introspect interface not available";
        return deviceList;
    }

    QDBusMessage reply = introspect.call("Introspect");

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Introspect error:" << reply.errorMessage();
        return deviceList;
    }

    QString xml = reply.arguments().at(0).toString();

    // Find all device nodes (dev_XX_XX_XX_XX_XX_XX)
    QRegularExpression regex("node name=\"(dev_[^\"]+)\"");
    QRegularExpressionMatchIterator matches = regex.globalMatch(xml);

    while (matches.hasNext()) {
        QRegularExpressionMatch match = matches.next();
        QString deviceNode = match.captured(1);
        QString devicePath = "/org/bluez/hci0/" + deviceNode;

        // Get device properties
        QDBusInterface deviceInterface(
            "org.bluez",
            devicePath,
            "org.bluez.Device1",
            QDBusConnection::systemBus()
            );

        if (!deviceInterface.isValid()) {
            qDebug() << "Invalid device:" << devicePath;
            continue;
        }

        QString name = deviceInterface.property("Name").toString();
        QString address = deviceInterface.property("Address").toString();
        bool paired = deviceInterface.property("Paired").toBool();

        if (name.isEmpty()) {
            qDebug() << "Skipping unnamed device:" << address;
            continue;
        }

        BluetoothDevice device(name, address, paired);
        deviceList.append(device);

        qDebug() << "Found device:" << name << address << "Paired:" << paired;
    }

    qDebug() << "Total devices found:" << deviceList.size();
    return deviceList;
}

bool bluetoothManager::disconnectFrom(const QString &address)
{
    // Convert address to path: AA:BB:CC:DD:EE:FF → /org/bluez/hci0/dev_AA_BB_CC_DD_EE_FF
    QString path = "/org/bluez/hci0/dev_" + QString(address).replace(":", "_");

    QDBusInterface deviceInterface(
        "org.bluez",
        path,
        "org.bluez.Device1",
        QDBusConnection::systemBus()
        );

    if (!deviceInterface.isValid()) {
        qDebug() << "Bluetooth Device Interface isn't available";
        return false;
    }

    qDebug() << "Disconnecting from:" << address;
    QDBusMessage reply = deviceInterface.call("Disconnect");

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Disconnect failed:" << reply.errorMessage();
        return false;
    }

    qDebug() << "Disconnected successfully";
    return true;
}

bool bluetoothManager::activate(QString const& address)
{
    QString path = "/org/bluez/hci0/dev_" + QString(address).replace(":", "_");

    QDBusInterface deviceInterface(
        "org.bluez",
        path,
        "org.bluez.Device1",
        QDBusConnection::systemBus()
        );

    if (!deviceInterface.isValid()) {
        qDebug() << "Bluetooth Device Interface isn't available";
        return false;
    }

    qDebug() << "Connecting to:" << address;
    QDBusMessage reply = deviceInterface.call("Connect");

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Connect failed:" << reply.errorMessage();
        return false;
    }

    qDebug() << "Connected successfully";
    return true;
}

bool bluetoothManager::connectTo(const QString &target ,QString const& password)
{
    Q_UNUSED(password);
    return pair(target);
}

bool bluetoothManager::pair(const QString& address)
{
    QString path = "/org/bluez/hci0/dev_" + QString(address).replace(":", "_");

    QDBusInterface deviceInterface(
        "org.bluez",
        path,
        "org.bluez.Device1",
        QDBusConnection::systemBus()
        );

    if (!deviceInterface.isValid()) {
        qDebug() << "Bluetooth Device Interface isn't available";
        return false;
    }

    qDebug() << "Pairing with:" << address;
    QDBusMessage reply = deviceInterface.call("Pair");

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Pair failed:" << reply.errorMessage();
        return false;
    }

    // After pairing, connect automatically
    deviceInterface.call("Connect");

    qDebug() << "Paired successfully";
    return true;
}



void bluetoothManager::onConfirmationRequested(const QString &devicePath, quint32 passkey)
{
    QString deviceName = pathToDeviceName(devicePath);
    qDebug() << "Confirmation requested for:" << deviceName << "Passkey:" << passkey;
    emit confirmationRequested(deviceName, passkey);
}

void bluetoothManager::onPairingComplete(bool success)
{
    emit pairingComplete(success);
}

QString bluetoothManager::pathToDeviceName(const QString &path)
{
    QDBusInterface deviceInterface(
        "org.bluez",
        path,
        "org.bluez.Device1",
        QDBusConnection::systemBus()
        );

    if (deviceInterface.isValid()) {
        return deviceInterface.property("Name").toString();
    }
    return path;
}



