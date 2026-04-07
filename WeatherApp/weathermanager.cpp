// #include "weathermanager.h"
// #include <QNetworkReply>
// #include <QJsonDocument>
// #include <QJsonObject>
// #include <QJsonArray>

// weatherManager::weatherManager(QObject *parent) : QObject(parent) ,
//     m_networkManager{new QNetworkAccessManager(this)} ,
//     m_apiKey{"94e24e15d89702e3b1144de5bb29b565"},
//     m_currentTemp{0}
// {
// }

// void weatherManager::fetchData(double lat , double lon)
// {
//     QString url = QString("https://api.openweathermap.org/data//onecall?lat=%1&lon=%2&appid=%3&units=metric&exclude=minutely,alerts")
//                       .arg(lat)
//                       .arg(lon)
//                       .arg(m_apiKey);

//     QNetworkReply *reply = m_networkManager->get(QNetworkRequest(QUrl(url)));

//     connect(reply, &QNetworkReply::finished, this, [this, reply]() {
//         if (reply->error() == QNetworkReply::NoError) {
//             parseData(reply->readAll());
//         } else {
//             emit errorOccurred(reply->errorString());
//         }
//         reply->deleteLater();
//     });
// }



// void weatherManager::parseData(const QByteArray &data)
// {
//     QJsonDocument doc = QJsonDocument::fromJson(data);
//     QJsonObject root = doc.object();

//     // Parse current weather
//     QJsonObject current = root["current"].toObject();
//     m_currentTemp = qRound(current["temp"].toDouble());

//     QJsonArray weather = current["weather"].toArray();
//     if (!weather.isEmpty()) {
//         QJsonObject w = weather[0].toObject();
//         m_currentCondition = w["description"].toString();
//         m_currentIcon = QString("https://openweathermap.org/img/wn/%1@2x.png")
//                             .arg(w["icon"].toString());
//     }

//     // Parse hourly forecast
//     m_hourlyForecast.clear();
//     QJsonArray hourly = root["hourly"].toArray();

//     for (const QJsonValue &h : hourly) {
//         QJsonObject obj = h.toObject();
//         QVariantMap hour;

//         hour["temp"] = qRound(obj["temp"].toDouble());

//         QJsonArray w = obj["weather"].toArray();
//         if (!w.isEmpty()) {
//             hour["condition"] = w[0].toObject()["description"].toString();
//             hour["icon"] = QString("https://openweathermap.org/img/wn/%1@2x.png")
//                                .arg(w[0].toObject()["icon"].toString());
//         }

//         m_hourlyForecast.append(hour);
//     }

//     // Parse daily forecast
//     m_dailyForecast.clear();
//     QJsonArray daily = root["daily"].toArray();

//     for (const QJsonValue &d : daily) {
//         QJsonObject obj = d.toObject();
//         QVariantMap day;

//         day["temp"] = qRound(obj["temp"].toObject()["day"].toDouble());

//         QJsonArray w = obj["weather"].toArray();
//         if (!w.isEmpty()) {
//             day["condition"] = w[0].toObject()["description"].toString();
//             day["icon"] = QString("https://openweathermap.org/img/wn/%1@2x.png")
//                               .arg(w[0].toObject()["icon"].toString());
//         }

//         m_dailyForecast.append(day);
//     }

//     emit weatherDataChanged();
// }


// // Getters
// int weatherManager::currentTemp() const { return m_currentTemp; }
// QString weatherManager::currentCondition() const { return m_currentCondition; }
// QString weatherManager::currentIcon() const { return m_currentIcon; }
// QVariantList weatherManager::hourlyForecast() const { return m_hourlyForecast; }
// QVariantList weatherManager::dailyForecast() const { return m_dailyForecast; }


#include "weathermanager.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

WeatherManager::WeatherManager(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_apiKey("98b498e87dbc4f2d814204715260704")  // Replace with your key
    , m_currentTemp(0)
{
}

void WeatherManager::fetchData(const QString &city)
{
    QString url = QString("https://api.weatherapi.com/v1/forecast.json?"
                          "key=%1&q=%2&days=3&aqi=no&alerts=no")
                      .arg(m_apiKey, city);

    QNetworkReply *reply = m_networkManager->get(QNetworkRequest(QUrl(url)));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            parseData(reply->readAll());
        } else {
            emit errorOccurred(reply->errorString());
        }
        reply->deleteLater();
    });
}

void WeatherManager::parseData(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    // Check for error
    if (root.contains("error")) {
        emit errorOccurred(root["error"].toObject()["message"].toString());
        return;
    }

    // Location
    m_cityName = root["location"].toObject()["name"].toString();

    // Current weather
    QJsonObject current = root["current"].toObject();
    m_currentTemp = qRound(current["temp_c"].toDouble());

    QJsonObject condition = current["condition"].toObject();
    m_currentCondition = condition["text"].toString();
    m_currentIcon = "https:" + condition["icon"].toString();

    // Daily forecast
    m_dailyForecast.clear();
    QJsonArray days = root["forecast"].toObject()["forecastday"].toArray();

    for (const QJsonValue &d : days) {
        QJsonObject obj = d.toObject();
        QJsonObject dayData = obj["day"].toObject();
        QJsonObject cond = dayData["condition"].toObject();

        QVariantMap day;
        day["date"] = obj["date"].toString();
        day["temp"] = qRound(dayData["avgtemp_c"].toDouble());
        day["tempMax"] = qRound(dayData["maxtemp_c"].toDouble());
        day["tempMin"] = qRound(dayData["mintemp_c"].toDouble());
        day["condition"] = cond["text"].toString();
        day["icon"] = "https:" + cond["icon"].toString();

        m_dailyForecast.append(day);
    }

    // Hourly forecast
    m_hourlyForecast.clear();

    if (!days.isEmpty()) {
        QJsonArray hours = days[0].toObject()["hour"].toArray();

        for (const QJsonValue &h : hours) {
            QJsonObject obj = h.toObject();
            QJsonObject cond = obj["condition"].toObject();

            QVariantMap hour;
            hour["time"] = obj["time"].toString().split(" ").last();
            hour["temp"] = qRound(obj["temp_c"].toDouble());
            hour["condition"] = cond["text"].toString();
            hour["icon"] = "https:" + cond["icon"].toString();

            m_hourlyForecast.append(hour);
        }
    }

    emit dataChanged();
}

// Getters
int WeatherManager::currentTemp() const { return m_currentTemp; }
QString WeatherManager::currentCondition() const { return m_currentCondition; }
QString WeatherManager::currentIcon() const { return m_currentIcon; }
QString WeatherManager::cityName() const { return m_cityName; }
QVariantList WeatherManager::hourlyForecast() const { return m_hourlyForecast; }
QVariantList WeatherManager::dailyForecast() const { return m_dailyForecast; }
