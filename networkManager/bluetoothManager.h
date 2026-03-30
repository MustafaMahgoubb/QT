#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include "INetworkInterface.h"
#include <QStringList>
#include <QtDBus/QDBusInterface>
#include <QList>
#include "BluetoothDevice.h"
#include "BluetoothAgent.h"


class bluetoothManager :public QObject , public INetworkInterface
{
    Q_OBJECT
public:
    explicit bluetoothManager(QObject *parent = nullptr);
    ~bluetoothManager() override;

    // INetworkInterface implementation
    Q_INVOKABLE bool enable() override;
    Q_INVOKABLE bool disable() override;
    Q_INVOKABLE bool isEnabled() override;

    bool connectTo(const QString &target ,QString const& password) override;
    Q_INVOKABLE bool activate(QString const& address) override;
    Q_INVOKABLE bool disconnectFrom(const QString &address) override;
    Q_INVOKABLE void scan() override;

    // Bluetooth specific
    Q_INVOKABLE QList<BluetoothDevice> getDevices();
    Q_INVOKABLE bool pair(const QString& address);




signals:
    void devicesFound(const QList<BluetoothDevice> &devices);
    void confirmationRequested(const QString &deviceName, quint32 passkey);
    void pairingComplete(bool success);

private slots:
    void onConfirmationRequested(const QString &devicePath, quint32 passkey);
    void onPairingComplete(bool success);

private:

    // Responsible for turning on/off bluetooth and scan devices
    QDBusInterface * m_bluetoothAdapterInterface;
    BluetoothAgent *m_agent;

    QString pathToDeviceName(const QString &path);
};

#endif // BLUETOOTHMANAGER_H
