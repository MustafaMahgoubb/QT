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

            Column {
                anchors.fill: parent
                anchors.margins: 30
                spacing: 25

                // Artifact Name
                Column {
                    spacing: 5
                    Text {
                        text: "Artifact Name:"
                        color: "#D4AF37"
                        font.pixelSize: 18
                        font.bold: true
                    }
                    Text {
                        text: "Golden Throne of Tutankhamun"
                        color: "white"
                        font.pixelSize: 24
                    }
                }

                // Period
                Column {
                    spacing: 5
                    Text {
                        text: "Period:"
                        color: "#D4AF37"
                        font.pixelSize: 18
                        font.bold: true
                    }
                    Text {
                        text: "New Kingdom (18th Dynasty)"
                        color: "white"
                        font.pixelSize: 24
                    }
                }

                // Description
                Column {
                    spacing: 5
                    width: parent.width

                    Text {
                        text: "Description:"
                        color: "#D4AF37"
                        font.pixelSize: 18
                        font.bold: true
                    }
                    Text {
                        text: "This beautifully decorated armchair was found wrapped in linen in the Antechamber. It is made of wood covered with sheets of gold that are both chased (pattern pressed into the metal) and inlaid with glass, faience and semi-precious stones. Side panels are formed from winged uraeus snakes holding the king’s cartouche. The scene on the front of backrest shows the king and queen under a floral canopy pierced by the rays of the Aten sun disk. Although adult-sized, this armchair must date from the beginning of Tutankhamun’s reign."
                        color: "white"
                        font.pixelSize: 18
                        width: parent.width
                        wrapMode: Text.WordWrap
                        lineHeight: 1.3
                    }
                }

                // Spacer
                Item {
                    Layout.fillHeight: true
                    height: 50
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
                        onClicked: {
                            goBack()
                        }
                    }
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
                rows: 2
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
                        source: "qrc:/Images/GOLDEN_THRONE1"
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
                        source: "qrc:/Images/GOLDEN_THRONE2"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                // Image 3
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
                        source: "qrc:/Images/GOLDEN_THRONE3"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                // Image 4
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
                        source: "qrc:/Images/GOLDEN_THRONE4"
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
