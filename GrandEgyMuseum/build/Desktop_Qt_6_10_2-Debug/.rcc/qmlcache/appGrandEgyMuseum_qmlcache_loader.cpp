#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_GrandEgyMuseum_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_FalconStatueScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_GodPtahStatueScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_GoldenThroneScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_HomeScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_RamssesObselikScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_SplashScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_GrandEgyMuseum_screensQml_TutankhamunScreen_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/FalconStatueScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_FalconStatueScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/GodPtahStatueScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_GodPtahStatueScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/GoldenThroneScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_GoldenThroneScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/HomeScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_HomeScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/RamssesObselikScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_RamssesObselikScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/SplashScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_SplashScreen_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/GrandEgyMuseum/screensQml/TutankhamunScreen.qml"), &QmlCacheGeneratedCode::_qt_qml_GrandEgyMuseum_screensQml_TutankhamunScreen_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appGrandEgyMuseum)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appGrandEgyMuseum))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_appGrandEgyMuseum)() {
    return 1;
}
