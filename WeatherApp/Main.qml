// import QtQuick
// import QtQuick.Controls



// ApplicationWindow {
//     width: 640
//     height: 480
//     visible: true
//     title: qsTr("Weather App")

//     color: '#2b2e2d'

//     Component.onCompleted: {
//         weatherManager.fetchData(30.0711, 31.0210)  // Cairo
//     }

//     // Add this to see errors
//     Connections {
//         target: weatherManager
//         function onErrorOccurred(error) {
//             console.log("API Error: " + error)
//             errorText.text = "Error: " + error
//         }
//         function onWeatherDataChanged() {
//             console.log("Data received! Temp: " + weatherManager.currentTemp)
//         }
//     }

//     // Error display
//     Text {
//         id: errorText
//         color: "red"
//         font.pixelSize: 14
//         anchors.top: parent.top
//         anchors.horizontalCenter: parent.horizontalCenter
//         anchors.topMargin: 10
//     }

//     // Text {
//     //     id: temperatureText
//     //     text: weatherManager.currentTemp + "°"
//     //     color: "white"
//     //     anchors.horizontalCenter: parent.horizontalCenter
//     //     anchors.top: parent.top
//     //     anchors.topMargin: 45
//     //     font.pixelSize: 128
//     //     font.bold: true
//     // }


//     ListView
//     {
//         id: daysListView
//         anchors.horizontalCenter: parent.horizontalCenter
//         anchors.bottom: parent.bottom
//         anchors.bottomMargin: 40
//         orientation: ListView.Horizontal

//         height: 160
//         width: parent.width - 40
//         spacing: 20
//         clip: true

//         model: ListModel {
//             ListElement { day: "Mon"; temp: 22; condition: "Sunny" ; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//             ListElement { day: "Tue"; temp: 24; condition: "Cloudy"; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//             ListElement { day: "Wed"; temp: 19; condition: "Rainy" ; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//             ListElement { day: "Thu"; temp: 21; condition: "Sunny" ; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//             ListElement { day: "Fri"; temp: 23; condition: "Sunny" ; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//             ListElement { day: "Sat"; temp: 25; condition: "Cloudy"; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//             ListElement { day: "Sun"; temp: 20; condition: "Rainy" ; icon : "https://cdn-icons-png.flaticon.com/512/5213/5213452.png" }
//         }

//         delegate: Rectangle {
//             width : 112.5
//             height: 150
//             radius: 15
//             color: "#3d4241"

//             Column {
//                 anchors.centerIn: parent
//                 spacing: 8

//                 Text {
//                     id: dayTxt
//                     text: qsTr(day)
//                     color: 'white'
//                     font.pixelSize: 18
//                     font.bold: true
//                     anchors.horizontalCenter: parent.horizontalCenter
//                 }

//                 Column {
//                     id: conditionState
//                     spacing: 4
//                     anchors.horizontalCenter: parent.horizontalCenter

//                     Image {
//                         id: conditionIcon
//                         source: icon
//                         width: 32
//                         height: 32
//                         anchors.horizontalCenter: parent.horizontalCenter
//                         // Fallback if no image
//                         onStatusChanged: {
//                             if (status === Image.Error) {
//                                 visible = false
//                             }
//                         }
//                     }

//                     Text {
//                         id: conditionTxt
//                         text: condition
//                         color: "#aaaaaa"
//                         font.pixelSize: 12
//                         anchors.horizontalCenter: parent.horizontalCenter
//                     }
//                 }

//                 Text {
//                     id: tempTxt
//                     text: temp + "°"
//                     color: 'white'
//                     font.pixelSize: 32
//                     font.bold: true
//                     anchors.horizontalCenter: parent.horizontalCenter
//                 }
//             }
//         }
//     }
// }


import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Weather App")
    color: '#2b2e2d'

    Component.onCompleted: {
        weatherManager.fetchData("Alexandria")
    }

    Connections {
        target: weatherManager
        function onErrorOccurred(error) {
            console.log("Error: " + error)
        }
    }

    // City name
    Text {
        id: cityText
        text: weatherManager.cityName
        color: "#888888"
        font.pixelSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    // Weather icon
    Image {
        id: weatherIcon
        source: weatherManager.currentIcon
        width: 64
        height: 64
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: cityText.bottom
        anchors.topMargin: 10
    }

    // Temperature
    Text {
        id: temperatureText
        text: weatherManager.currentTemp + "°"
        color: "white"
        font.pixelSize: 100
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: weatherIcon.bottom
    }

    // Condition
    Text {
        id: conditionText
        text: weatherManager.currentCondition
        color: "#888888"
        font.pixelSize: 18
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: temperatureText.bottom
    }

    // 3-Day Forecast
    ListView {
        id: daysListView
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        orientation: ListView.Horizontal
        height: 160
        spacing: 20
        clip: true


        property int itemWidth: 112
        property int itemCount: 3

        // Auto-calculate width
        width: (itemWidth * itemCount) + (spacing * (itemCount - 1))

        model: weatherManager.dailyForecast

        delegate: Rectangle {
            width: 112.5
            height: 150
            radius: 15
            color: "#3d4241"

            Column {
                anchors.centerIn: parent
                spacing: 5

                Text {
                    text: {
                        var date = new Date(modelData.date);
                        var days = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
                        return days[date.getDay()];
                    }
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Image {
                    source: modelData.icon
                    width: 45
                    height: 45
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: modelData.temp + "°"
                    color: "white"
                    font.pixelSize: 28
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: modelData.condition
                    color: "#aaaaaa"
                    font.pixelSize: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
