#include "BluetoothAgent.h"
#include <QDBusInterface>
#include <QDebug>

BluetoothAgent::BluetoothAgent(QObject *parent)
    : QObject(parent)
    , m_agentPath("/org/bluez/agent")
{
}

BluetoothAgent::~BluetoothAgent()
{
    unregisterAgent();
}

bool BluetoothAgent::registerAgent()
{
    qDebug() << "Registering Bluetooth agent...";

    // Register object on D-Bus
    bool registered = QDBusConnection::systemBus().registerObject(
        m_agentPath,
        this,
        QDBusConnection::ExportAllSlots
        );

    if (!registered) {
        qDebug() << "Failed to register agent object on D-Bus";
        return false;
    }

    qDebug() << "Agent object registered on D-Bus";

    // Register with BlueZ AgentManager
    QDBusInterface agentManager(
        "org.bluez",
        "/org/bluez",
        "org.bluez.AgentManager1",
        QDBusConnection::systemBus()
        );

    if (!agentManager.isValid()) {
        qDebug() << "AgentManager not available";
        return false;
    }

    // Use NoInputNoOutput for auto-accept
    QDBusMessage reply = agentManager.call(
        "RegisterAgent",
        QVariant::fromValue(QDBusObjectPath(m_agentPath)),
        QString("NoInputNoOutput")
        );

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Failed to register agent:" << reply.errorMessage();
        return false;
    }

    qDebug() << "Agent registered with BlueZ";

    // Make it default agent
    reply = agentManager.call(
        "RequestDefaultAgent",
        QVariant::fromValue(QDBusObjectPath(m_agentPath))
        );

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Failed to set default agent:" << reply.errorMessage();
        return false;
    }

    qDebug() << "Bluetooth agent registered successfully";
    return true;
}

void BluetoothAgent::unregisterAgent()
{
    QDBusInterface agentManager(
        "org.bluez",
        "/org/bluez",
        "org.bluez.AgentManager1",
        QDBusConnection::systemBus()
        );

    if (agentManager.isValid()) {
        agentManager.call(
            "UnregisterAgent",
            QVariant::fromValue(QDBusObjectPath(m_agentPath))
            );
    }

    QDBusConnection::systemBus().unregisterObject(m_agentPath);
    qDebug() << "Bluetooth agent unregistered";
}

void BluetoothAgent::Release()
{
    qDebug() << "Agent released";
}

QString BluetoothAgent::RequestPinCode(const QDBusObjectPath &device)
{
    qDebug() << "PIN requested for:" << device.path();
    return "0000";
}

void BluetoothAgent::DisplayPinCode(const QDBusObjectPath &device, const QString &pincode)
{
    qDebug() << "Display PIN:" << pincode << "for" << device.path();
}

quint32 BluetoothAgent::RequestPasskey(const QDBusObjectPath &device)
{
    qDebug() << "Passkey requested for:" << device.path();
    return 0;
}

void BluetoothAgent::DisplayPasskey(const QDBusObjectPath &device, quint32 passkey, quint16 entered)
{
    Q_UNUSED(entered)
    qDebug() << "Display passkey:" << passkey << "for" << device.path();
}

void BluetoothAgent::RequestConfirmation(const QDBusObjectPath &device, quint32 passkey)
{
    qDebug() << "=== AUTO-ACCEPTING PAIRING ===";
    qDebug() << "Device:" << device.path();
    qDebug() << "Passkey:" << passkey;

    emit pairingRequested(device.path(), passkey);

    // Auto-accept: just return without error
    // BlueZ interprets this as "confirmed"
}

void BluetoothAgent::RequestAuthorization(const QDBusObjectPath &device)
{
    qDebug() << "Authorization requested for:" << device.path();
    // Auto-authorize
}

void BluetoothAgent::AuthorizeService(const QDBusObjectPath &device, const QString &uuid)
{
    qDebug() << "Authorize service:" << uuid << "for" << device.path();
}

void BluetoothAgent::Cancel()
{
    qDebug() << "Pairing cancelled";
    emit pairingComplete(false);
}
