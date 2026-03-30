#ifndef BLUETOOTHAGENT_H
#define BLUETOOTHAGENT_H

#include <QObject>
#include <QDBusObjectPath>
#include <QDBusConnection>

class BluetoothAgent : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.bluez.Agent1")

public:
    explicit BluetoothAgent(QObject *parent = nullptr);
    ~BluetoothAgent() override;

    bool registerAgent();
    void unregisterAgent();

public slots:
    void Release();
    QString RequestPinCode(const QDBusObjectPath &device);
    void DisplayPinCode(const QDBusObjectPath &device, const QString &pincode);
    quint32 RequestPasskey(const QDBusObjectPath &device);
    void DisplayPasskey(const QDBusObjectPath &device, quint32 passkey, quint16 entered);
    void RequestConfirmation(const QDBusObjectPath &device, quint32 passkey);
    void RequestAuthorization(const QDBusObjectPath &device);
    void AuthorizeService(const QDBusObjectPath &device, const QString &uuid);
    void Cancel();

signals:
    void pairingRequested(const QString &devicePath, quint32 passkey);
    void pairingComplete(bool success);

private:
    QString m_agentPath;
};

#endif // BLUETOOTHAGENT_H
