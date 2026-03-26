#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include "INetworkInterface.h"
#include <QObject>
#include <QStringList>
#include <QtDBus/QDBusInterface>

class WifiManager : public QObject, public INetworkInterface
{
    Q_OBJECT

public:
    explicit WifiManager(QObject *parent = nullptr);
    ~WifiManager() override;

    // INetworkInterface implementation
    Q_INVOKABLE bool enable() override;
    Q_INVOKABLE bool disable() override;
    Q_INVOKABLE bool isEnabled() override;

    Q_INVOKABLE QString findSavedConnection(const QString &ssID) override;
    Q_INVOKABLE bool connectTo(const QString &target ,QString const& password) override;
    Q_INVOKABLE bool activate(QString const& path) override;
    Q_INVOKABLE bool disconnectFrom(const QString &target) override;

    // WiFi specific
    Q_INVOKABLE void scan();
    Q_INVOKABLE QStringList getNetworks();

signals:
    void wifiStateChanged(bool enabled);
    void networksFound(const QStringList &networks);
    void connectionChanged(bool connected);

private slots:
    void onPropertiesChanged(const QString &interface,
                             const QVariantMap &changed,
                             const QStringList &invalidated);

private:
    // Main NetworkManager	Global settings (enable/disable WiFi)
    QDBusInterface *m_networkManagerInterface;
};



#endif // WIFIMANAGER_H
