// #ifndef WEATHERMANAGER_H
// #define WEATHERMANAGER_H

// #include <QObject>
// #include <QVariantList>
// #include <QNetworkAccessManager>

// class weatherManager : public QObject
// {
//     Q_OBJECT

//     // Current weather properties
//     Q_PROPERTY(int currentTemp READ currentTemp NOTIFY weatherDataChanged)
//     Q_PROPERTY(QString currentCondition READ currentCondition NOTIFY weatherDataChanged)
//     Q_PROPERTY(QString currentIcon READ currentIcon NOTIFY weatherDataChanged)

//     // Lists for QML
//     Q_PROPERTY(QVariantList hourlyForecast READ hourlyForecast NOTIFY weatherDataChanged)
//     Q_PROPERTY(QVariantList dailyForecast READ dailyForecast NOTIFY weatherDataChanged)


// signals:
//     void weatherDataChanged();
//     void errorOccurred(const QString &error);

// public:
//     explicit weatherManager(QObject *parent = nullptr);
//     Q_INVOKABLE void fetchData(double lat, double lon);

//     // Getters
//     int currentTemp() const;
//     QString currentCondition() const;
//     QString currentIcon() const;
//     QVariantList hourlyForecast() const;
//     QVariantList dailyForecast() const;

// private:

//     void parseData(const QByteArray &data);

//     QNetworkAccessManager *m_networkManager;
//     QString m_apiKey;

//     // Current weather
//     int m_currentTemp;
//     QString m_currentCondition;
//     QString m_currentIcon;

//     // Hourly forecast
//     QVariantList m_hourlyForecast;

//     // Daily forecast
//     QVariantList m_dailyForecast;
// };

// #endif // WEATHERMANAGER_H



#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QObject>
#include <QVariantList>
#include <QNetworkAccessManager>

class WeatherManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentTemp READ currentTemp NOTIFY dataChanged)
    Q_PROPERTY(QString currentCondition READ currentCondition NOTIFY dataChanged)
    Q_PROPERTY(QString currentIcon READ currentIcon NOTIFY dataChanged)
    Q_PROPERTY(QString cityName READ cityName NOTIFY dataChanged)
    Q_PROPERTY(QVariantList hourlyForecast READ hourlyForecast NOTIFY dataChanged)
    Q_PROPERTY(QVariantList dailyForecast READ dailyForecast NOTIFY dataChanged)

public:
    explicit WeatherManager(QObject *parent = nullptr);

    Q_INVOKABLE void fetchData(const QString &city);

    int currentTemp() const;
    QString currentCondition() const;
    QString currentIcon() const;
    QString cityName() const;
    QVariantList hourlyForecast() const;
    QVariantList dailyForecast() const;

signals:
    void dataChanged();
    void errorOccurred(const QString &error);

private:
    void parseData(const QByteArray &data);

    QNetworkAccessManager *m_networkManager;
    QString m_apiKey;

    int m_currentTemp;
    QString m_currentCondition;
    QString m_currentIcon;
    QString m_cityName;
    QVariantList m_hourlyForecast;
    QVariantList m_dailyForecast;
};

#endif // WEATHERMANAGER_H
