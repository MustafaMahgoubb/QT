import QtQuick
import QtQuick.Layouts

Rectangle {
    id: detailRoot
    color: "#1a1a2e"

    signal goBack()

    // Main Layout - Left and Right
    RowLayout {
        anchors.fill: parent
        anchors.margins: 40
        spacing: 40

        // ══════════════════════════════
        // LEFT SIDE - Info + Back Button
        // ══════════════════════════════
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.4
            color: "#2a2a4e"
            radius: 15
            clip: true

            Flickable {
                id: flickable
                anchors.fill: parent
                anchors.margins: 30
                contentHeight: contentColumn.height
                clip: true

                Column {
                    id: contentColumn
                    width: parent.width
                    spacing: 25

                    // Artifact Name
                    Column {
                        width: parent.width
                        spacing: 5

                        Text {
                            text: "Artifact Name:"
                            color: "#D4AF37"
                            font.pixelSize: 18
                            font.bold: true
                        }
                        Text {
                            text: "Obelisk of King Ramesses II"
                            color: "white"
                            font.pixelSize: 24
                            width: parent.width
                            wrapMode: Text.WordWrap
                        }
                    }

                    // Period
                    Column {
                        width: parent.width
                        spacing: 5

                        Text {
                            text: "Period:"
                            color: "#D4AF37"
                            font.pixelSize: 18
                            font.bold: true
                        }
                        Text {
                            text: "New Kingdom (19th Dynasty)"
                            color: "white"
                            font.pixelSize: 24
                            width: parent.width
                            wrapMode: Text.WordWrap
                        }
                    }

                    // Description
                    Column {
                        width: parent.width
                        spacing: 5

                        Text {
                            text: "Description:"
                            color: "#D4AF37"
                            font.pixelSize: 18
                            font.bold: true
                        }
                        Text {
                            text: "Ramesses II raised over ten obelisks at Tanis (San el-Hagar) in the Eastern Delta. With a total height of 16 meters, this granite obelisk is the highest that ever stood at Tanis. On the four sides of the obelisk are inscriptions giving the Horus name, throne name and the birth name of the king. The 87-ton obelisk is now lifted on a platform supported by four massive pillars on a huge concrete base to allow visitors of the Grand Egyptian Museum to view the cartouches of Ramesses II carved on its bottom. Placed in a square of 30,000 m2, the Hanging Obelisk is the first artefact welcoming visitors at the Grand Egyptian Museum."
                            color: "white"
                            font.pixelSize: 18
                            width: parent.width
                            wrapMode: Text.WordWrap
                            lineHeight: 1.3
                        }
                    }

                    // Spacer before back button
                    Item {
                        width: 1
                        height: 30
                    }

                    // Back Button
                    Rectangle {
                        width: 150
                        height: 50
                        color: "#D4AF37"
                        radius: 10

                        Text {
                            anchors.centerIn: parent
                            text: "← Back"
                            color: "#1a1a2e"
                            font.pixelSize: 20
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: goBack()
                        }
                    }
                }
            }

            // Optional: Scroll Indicator
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: 6
                radius: 3
                color: "#444"
                visible: flickable.contentHeight > flickable.height

                Rectangle {
                    width: parent.width
                    height: Math.max(30, parent.height * (flickable.height / flickable.contentHeight))
                    radius: 3
                    color: "#D4AF37"
                    y: (parent.height - height) * (flickable.contentY / (flickable.contentHeight - flickable.height))
                }
            }
        }

        // ══════════════════════════════
        // RIGHT SIDE - Image Grid
        // ══════════════════════════════
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            GridLayout {
                anchors.centerIn: parent
                columns: 2
                rows: 1
                rowSpacing: 20
                columnSpacing: 20

                // Image 1
                Rectangle {
                    Layout.preferredWidth: 300
                    Layout.preferredHeight: 300
                    color: "transparent"
                    border.color: "#D4AF37"
                    border.width: 3
                    radius: 10

                    Image {
                        anchors.fill: parent
                        anchors.margins: 5
                        source: "qrc:/Images/RAMESSES_OBSELIK1"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                // Image 2
                Rectangle {
                    Layout.preferredWidth: 300
                    Layout.preferredHeight: 300
                    color: "transparent"
                    border.color: "#D4AF37"
                    border.width: 3
                    radius: 10

                    Image {
                        anchors.fill: parent
                        anchors.margins: 5
                        source: "qrc:/Images/RAMESSES_OBSELIK2"
                        fillMode: Image.PreserveAspectFit
                    }
                }


            }
        }
    }
}
