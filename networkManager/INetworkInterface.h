#ifndef INETWORKINTERFACE_H
#define INETWORKINTERFACE_H

#include <QString>

class INetworkInterface
{
public:
    virtual ~INetworkInterface() = default;

    virtual bool enable() = 0;
    virtual bool disable() = 0;
    virtual bool isEnabled() = 0;
    virtual bool connectTo(const QString &target ,QString const& password) = 0;
    virtual bool activate(QString const& path) = 0;
    virtual bool disconnectFrom(const QString &target) = 0;
    virtual void scan() = 0;

protected:
    INetworkInterface() = default;
};

#endif // INETWORKINTERFACE_H
