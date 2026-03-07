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
                            text: "Statue of God Ptah, King Ramesses II and Goddess Sekhmet"
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
                            text: "Discovered in 1904 near the courtyard of the Temple of Heryshef at Herakleopolis Magna (Ihnasya el-Medina), this red granite colossal represents King Ramesses II standing between god Ptah and goddess Sekhmet. Ptah, a god of craftsmen, whose cult was centred at Memphis, is shown mummy-shaped wearing a skull cap, a royal beard and holding a staff. His consort, the warrior goddess Sekhmet, is depicted with a lioness head topped with a sun disk and a protective uraeus snake. The central figure of King Ramesses II is muscular with broad shoulders and powerful upper arms. With its carefully modelled anatomical details, such as the protruding collarbones, rounded pectoral muscles, the remarkable kneecaps and the salient tibia bone, the King's figure can hardly skip the attention of the viewer. Ramesses II wears a blue crown, also known as the khepresh crown, a pleated royal kilt (shendyt) ornamented with a leopard pendant and seven cobras, each crowned with a sun disk. On his right shoulder, he holds a crook, symbol of his kingship. His left arm extends along his body, touching the right hand of the goddess. It appears from the inscriptions carved on the statue base and the back pillar that the figure of goddess Sekhmet replaced an earlier figure of god Harsaphes. Nine vertical columns of text, incised on the back pillar, name King Ramesses II as the 'beloved of' the deities: Ptah, Horus, Heryshef, Bastet, Atum and Amun-Re."
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
                        source: "qrc:/Images/GOD_PTAH_STATUE1"
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
                        source: "qrc:/Images/GOD_PTAH_STATUE2"
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
                        source: "qrc:/Images/GOD_PTAH_STATUE3"
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
                        source: "qrc:/Images/GOD_PTAH_STATUE4"
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
