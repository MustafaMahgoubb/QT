import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: homeScreenID
    color: "#1a1a2e"  // Fallback color while image loads

    signal openPage(string pageSource)

    Rectangle {
        id: topBar
        width: parent.width
        height: 40
        color: '#624223'
        anchors.top: parent.top

        // Timer updates every second
        Timer {
            id: clockTimer
            interval: 1000
            running: true
            repeat: true
            triggeredOnStart: true
            onTriggered: {
                var now = new Date()
                timeText.text = Qt.formatTime(now, "hh:mm AP")
                dateText.text = Qt.formatDate(now, "dd MMM yyyy")
            }
        }

        // Time (left)
        Text {
            id: timeText
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: "--:-- --"
            color: "white"
            font.pixelSize: 18
        }

        // Date (center)
        Text {
            id: dateText
            anchors.centerIn: parent
            text: "-- --- ----"
            color: "white"
            font.pixelSize: 18
        }

        // Temperature (right)
        Text {
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: "28°C"
            color: "white"
        }
    }

    Image {
        id: backgroundImage
        source: "qrc:/Images/BACKGROUND"
        width: parent.width
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        fillMode: Image.PreserveAspectCrop
    }

    Item{
        id: contentArea
        anchors.top: topBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom


        Rectangle{
            id: galleryID
            width: galleryText.implicitWidth + 20
            height: 60
            anchors.topMargin: 30
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#624223"
            Text {
                id: galleryText
                anchors.centerIn: parent
                text: qsTr("Gallery")
                font.pixelSize: 48
                color: "#D4AF37"
            }
        }



        ListView {
            id: photoSlider

            anchors.centerIn: parent
            width: parent.width
            height: 480
            currentIndex: 1

            orientation: ListView.Horizontal
            snapMode: ListView.SnapOneItem
            clip: true

            highlight: Item {
                width: photoSlider.width / 3
                height: photoSlider.height

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 15          // Slightly less than image margin (20)
                    color: "transparent"
                    border.color: "#D4AF37"
                    border.width: 5
                    radius: 10
                }
            }

            highlightFollowsCurrentItem: true
            highlightMoveDuration: 300

            model: ListModel {
                ListElement {
                    imgSource: "qrc:/Images/GOLDEN_THRONE1"
                    pageSource: "screensQml/GoldenThroneScreen.qml"
                }
                ListElement {
                    imgSource: "qrc:/Images/TUTANKHAMUN1"
                    pageSource: "screensQml/TutankhamunScreen.qml"
                }
                ListElement {
                    imgSource: "qrc:/Images/FALCON_STATUE1"
                    pageSource: "screensQml/FalconStatueScreen.qml"
                }
                ListElement {
                    imgSource: "qrc:/Images/RAMESSES_OBSELIK1"
                    pageSource: "screensQml/RamssesObselikScreen.qml"
                }
                ListElement {
                    imgSource: "qrc:/Images/GOD_PTAH_STATUE1"
                    pageSource: "screensQml/GodPtahStatueScreen.qml"
                }
            }

            delegate: Item {
                width: photoSlider.width / 3
                height: photoSlider.height

                Image {
                    anchors.fill: parent
                    anchors.margins: 20
                    source: model.imgSource
                    fillMode: Image.PreserveAspectCrop
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        photoSlider.currentIndex = index
                        homeScreenID.openPage(model.pageSource)

                    }
                }
            }
        }
    }


}
