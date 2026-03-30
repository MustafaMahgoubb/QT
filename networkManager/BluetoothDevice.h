#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QString>
#include <QObject>
#include <QMetaType>

class BluetoothDevice
{
    Q_GADGET
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString address MEMBER address)
    Q_PROPERTY(bool paired MEMBER paired)

public:
    BluetoothDevice() = default;
    BluetoothDevice(const QString &n, const QString &addr, bool p)
        : name(n), address(addr), paired(p) {}

    QString name;
    QString address;
    bool paired = false;
};

// Register the type with Qt's meta-object system
Q_DECLARE_METATYPE(BluetoothDevice)

#endif // BLUETOOTHDEVICE_H
