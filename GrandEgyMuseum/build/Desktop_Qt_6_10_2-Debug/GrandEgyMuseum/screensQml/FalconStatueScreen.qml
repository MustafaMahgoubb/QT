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
                            text: "Statuette of a Falcon"
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
                            text: "Late Period (26th Dynasty)"
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
                            text: "This gilt bronze votive statuette of a hawk was discovered in 1893 at Sais (Sa-al-Hagar) in the western Delta and is dated to Dynasty 26. The statuette was made using the lost-wax technique in which a wax model was enclosed in clay and allowed to dry. The wax was then melted before the molten metal was poured into the resulting clay mould. Gold was used here to highlight the falcon’s head, plumage and jewellery. The statuette shows the avian form of god Horus, who was associated with kingship, wearing a crown (now partly broken) and a broad gilded collar ending in a solar-heart amulet. This amulet was probably used by ancient Egyptian kings as an attribute of god Horus, therefore, indicating the divine status of the king. The solar disk above the heart identified the king’s heart with the sun and may have signalled his ability to maintain maat (justice) in the same way the sun illuminated the universe. Such votive statuettes were donated to the temple to honour its deities. The gilded dedicatory text on the base of the statuette names a certain Imhotep, son of Padineith. By naming the dedicant in the inscription, he could magically participate in the daily temple rituals that common people were not allowed to attend."
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
                        source: "qrc:/Images/FALCON_STATUE1"
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
                        source: "qrc:/Images/FALCON_STATUE2"
                        fillMode: Image.PreserveAspectFit
                    }
                }


            }
        }
    }
}
