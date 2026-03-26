#include "wifimanager.h"
#include <QDBusConnection>
#include <QDBusInterface>
#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusArgument>

WifiManager::WifiManager(QObject *parent) : QObject{parent}
{
    // set up D-Bus Connection
    m_networkManagerInterface = new QDBusInterface("org.freedesktop.NetworkManager",
                                                   "/org/freedesktop/NetworkManager",
                                                   "org.freedesktop.NetworkManager" ,
                                                   QDBusConnection::systemBus(),
                                                   this);

    // Check if connection works
    if (m_networkManagerInterface->isValid()) {
        qDebug() << "Connected to NetworkManager!";
    } else {
        qDebug() << "Failed to connect to NetworkManager!";
    }

    // Listen for LastScan property change
    bool connected = QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Devices/3",
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(onPropertiesChanged(QString,QVariantMap,QStringList))
        );

    if (connected) {
        qDebug() << "Listening for scan updates!";
    } else {
        qDebug() << "Failed to connect signal!";
    }
}

WifiManager::~WifiManager() = default;

bool WifiManager::isEnabled()
{
    bool state = m_networkManagerInterface->property("WirelessEnabled").toBool();
    return state;
}

bool WifiManager::enable()
{
    return m_networkManagerInterface->setProperty("WirelessEnabled",true);
}

bool WifiManager::disable()
{
    return m_networkManagerInterface->setProperty("WirelessEnabled",false);
}

QString WifiManager::findSavedConnection(QString const& ssID)
{
    QString path = "";

    QDBusInterface wifiInt("org.freedesktop.NetworkManager",
                           "/org/freedesktop/NetworkManager/Settings",
                           "org.freedesktop.NetworkManager.Settings" ,
                           QDBusConnection::systemBus()
                           );

    if (!wifiInt.isValid())
    {
        // return empty Path
        qDebug() << "Invalid Settings Interface";
        return path;
    }

    QDBusMessage reply = wifiInt.call("ListConnections");

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Error:" << reply.errorMessage();
        return path;
    }

    QDBusArgument arg = reply.arguments().at(0).value<QDBusArgument>();
    QList<QDBusObjectPath> connections;
    arg >> connections;

    for (const QDBusObjectPath &currPath : connections)
    {
        // From org.freedesktop.NetworkManager.Settings.Connection get this path Info
        QDBusInterface currSetting("org.freedesktop.NetworkManager",
                                   currPath.path(),
                                   "org.freedesktop.NetworkManager.Settings.Connection",
                                   QDBusConnection::systemBus());

        if (!currSetting.isValid())
        {
            continue;
        }

        QDBusMessage currReply = currSetting.call("GetSettings");
        if (currReply.type() == QDBusMessage::ErrorMessage) {
            continue;
        }


        // Check if the current ssID matches the Required ssID

        // Extract settings map to get current ssID
        QDBusArgument settingsArg = currReply.arguments().at(0).value<QDBusArgument>();
        QMap<QString, QVariantMap> settings;
        settingsArg >> settings;

        // Skip non-wireless connections
        if (!settings.contains("802-11-wireless")) {
            continue;
        }

        // Get SSID
        QVariantMap wirelessSettings = settings["802-11-wireless"];

        if (wirelessSettings.contains("ssid")) {
            QByteArray ssidBytes = wirelessSettings["ssid"].toByteArray();
            QString currSSID = QString::fromUtf8(ssidBytes);

            if (currSSID == ssID) {
                path = currPath.path();
                qDebug() << "Found saved connection for" << ssID << "at" << path;
                break;
            }
        }
    }
    return path;
}

bool WifiManager::activate(QString const& path)
{
    if (!(m_networkManagerInterface->isValid()))
    {
        qDebug() << "Failed to Connect to NetworkManager";
        return false;
    }

    QDBusMessage reply = m_networkManagerInterface->call("ActivateConnection",
                                                         QVariant::fromValue(QDBusObjectPath(path)),
                                                         QVariant::fromValue(QDBusObjectPath("/org/freedesktop/NetworkManager/Devices/3")),
                                                         QVariant::fromValue(QDBusObjectPath("/")));

    if(reply.type() == QDBusMessage::ErrorMessage)
    {
        qDebug() << "Connection failed:" << reply.errorMessage();
        return false;
    }

    return true;
}


bool WifiManager::connectTo(QString const& ssID , QString const& password)
{

    if (!m_networkManagerInterface->isValid())
    {
        qDebug() << "Invalid wifi Interface, returning from function ...";
        return false;
    }


    // Build inner Maps
    QVariantMap connectionSettings;
    connectionSettings["id"] = ssID;
    connectionSettings["type"] = "802-11-wireless";

    QVariantMap wireless;
    wireless["ssid"] = ssID.toUtf8();  // Must be QByteArray
    wireless["mode"] = "infrastructure";

    QVariantMap security;
    security["key-mgmt"] = "wpa-psk";
    security["psk"] = password;

    QVariantMap ipv4;
    ipv4["method"] = "auto";

    // Build outer map: a{sa{sv}}
    QMap<QString, QVariantMap> connection;
    connection["connection"] = connectionSettings;
    connection["802-11-wireless"] = wireless;
    connection["802-11-wireless-security"] = security;
    connection["ipv4"] = ipv4;

    // Encode properly for D-Bus
    QDBusArgument arg;
    arg.beginMap(QMetaType::fromType<QString>(), QMetaType::fromType<QVariantMap>());

    for (auto it = connection.begin(); it != connection.end(); ++it) {
        arg.beginMapEntry();
        arg << it.key() << it.value();
        arg.endMapEntry();
    }

    arg.endMap();


    QDBusMessage reply = m_networkManagerInterface->call("AddAndActivateConnection",
                                                         QVariant::fromValue(arg),
                                                         QVariant::fromValue(QDBusObjectPath("/org/freedesktop/NetworkManager/Devices/3")),
                                                         QVariant::fromValue(QDBusObjectPath("/"))
                                                         );

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Connection failed:" << reply.errorMessage();
        return false;
    }

    qDebug() << "Connected to:" << ssID;
    return true;
}

bool WifiManager::disconnectFrom(QString const& obj)
{
    return 0;
}

void WifiManager::scan()
{
    QDBusInterface wirelessInt("org.freedesktop.NetworkManager",
                               "/org/freedesktop/NetworkManager/Devices/3",
                               "org.freedesktop.NetworkManager.Device.Wireless",
                               QDBusConnection::systemBus());

    if(!wirelessInt.isValid())
    {
        qDebug() << "Invalid Interface ... returning from function";
        return ;
    }


    // Call method with empty options dictionary
    QDBusMessage reply = wirelessInt.call("RequestScan", QVariantMap());

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Scan failed:" << reply.errorMessage();
    } else {
        qDebug() << "Scan started!";
    }
    return;
}


QStringList WifiManager::getNetworks()
{
    QDBusInterface wirelessInt(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Devices/3",
        "org.freedesktop.NetworkManager.Device.Wireless",
        QDBusConnection::systemBus()
        );

    QStringList networkList;

    if (!wirelessInt.isValid()) {
        qDebug() << "Invalid Interface!";
        return networkList;
    }

    QDBusMessage reply = wirelessInt.call("GetAccessPoints");

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Error:" << reply.errorMessage();
        return networkList;
    }

    // Extract QDBusArgument from reply
    QDBusArgument arg = reply.arguments().at(0).value<QDBusArgument>();

    // Extract object paths from argument
    QList<QDBusObjectPath> accessPoints;
    arg >> accessPoints;

    qDebug() << "Found" << accessPoints.size() << "access points";

    // For each AccessPoint, get SSID
    for (const QDBusObjectPath &apPath : accessPoints) {

        QDBusInterface apInterface(
            "org.freedesktop.NetworkManager",
            apPath.path(),
            "org.freedesktop.NetworkManager.AccessPoint",
            QDBusConnection::systemBus()
            );

        if (apInterface.isValid()) {
            QByteArray ssidBytes = apInterface.property("Ssid").toByteArray();
            QString ssid = QString::fromUtf8(ssidBytes);

            if (!ssid.isEmpty() && !networkList.contains(ssid)) {
                networkList.append(ssid);
                qDebug() << "Found SSID:" << ssid;
            }
        }
    }

    qDebug() << "Total networks:" << networkList;
    return networkList;
}

void WifiManager::onPropertiesChanged(const QString &interface,
                                      const QVariantMap &changed,
                                      const QStringList &invalidated)
{
    Q_UNUSED(invalidated)

    if (interface == "org.freedesktop.NetworkManager.Device.Wireless") {
        if (changed.contains("LastScan")) {
            qDebug() << "Scan completed!";
            emit networksFound(getNetworks());
        }
    }
}


