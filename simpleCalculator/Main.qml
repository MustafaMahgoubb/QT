import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    visible: true
    width: 350
    height: 500
    title: "Calculator"

    Rectangle {
        id: calculatorBodyId
        anchors.fill: parent
        color: "#2c3e50"

        // ============== DISPLAY SCREEN ==============
        Rectangle {
            id: screenId
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: 0.2 * parent.height
            radius: 15
            color: "#1a252f"
            border.color: "#34495e"
            border.width: 2

            // Display text - bound to C++ backend
            Text {
                id: displayText
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 20

                // BIND TO C++ PROPERTY
                text: calc.displayValue

                color: "#ecf0f1"
                font.pixelSize: 48
                font.bold: true
                horizontalAlignment: Text.AlignRight
                elide: Text.ElideLeft  // Truncate from left if too long
            }
        }

        // ============== BUTTONS GRID ==============
        GridLayout {
            id: buttonsLayout
            anchors.top: screenId.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            columns: 4
            rowSpacing: 10
            columnSpacing: 10

            Repeater {
                model: [
                    // Row 1
                    {text: "C", color: "#e74c3c", pressedColor: "#c0392b", type: "clear"},
                    {text: "⌫", color: "#e67e22", pressedColor: "#d35400", type: "backspace"},
                    {text: ".", color: "#34495e", pressedColor: "#2c3e50", type: "decimal"},
                    {text: "÷", color: "#9b59b6", pressedColor: "#8e44ad", type: "operator"},

                    // Row 2
                    {text: "7", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "8", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "9", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "×", color: "#3498db", pressedColor: "#2980b9", type: "operator"},

                    // Row 3
                    {text: "4", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "5", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "6", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "-", color: "#f39c12", pressedColor: "#e67e22", type: "operator"},

                    // Row 4
                    {text: "1", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "2", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "3", color: "#34495e", pressedColor: "#2c3e50", type: "digit"},
                    {text: "+", color: "#f39c12", pressedColor: "#e67e22", type: "operator"},

                    // Row 5
                    {text: "0", color: "#34495e", pressedColor: "#2c3e50", type: "digit", span: 2},
                    {text: "=", color: "#2ecc71", pressedColor: "#27ae60", type: "equals", span: 2}
                ]

                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.columnSpan: modelData.span ? modelData.span : 1

                    text: modelData.text
                    font.pixelSize: 28
                    font.bold: true

                    contentItem: Text {
                        text: parent.text
                        font: parent.font
                        color: "#ecf0f1"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        color: parent.pressed ? modelData.pressedColor : modelData.color
                        radius: 10
                    }

                    // ============== CONNECT TO C++ BACKEND ==============
                    onClicked: {
                        switch(modelData.type) {
                            case "digit":
                                calc.digitPressed(parseInt(modelData.text))
                                break
                            case "decimal":
                                calc.decimalPressed()
                                break
                            case "operator":
                                calc.operationPressed(modelData.text)
                                break
                            case "equals":
                                calc.equalPressed()
                                break
                            case "clear":
                                calc.clear()
                                break
                            case "backspace":
                                calc.backspace()
                                break
                        }
                    }
                }
            }
        }

        // ============== ERROR DISPLAY ==============
        Rectangle {
            id: errorPopup
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: buttonsLayout.top
            anchors.bottomMargin: 10
            width: parent.width * 0.8
            height: 40
            radius: 10
            color: "#e74c3c"
            visible: false

            Text {
                id: errorText
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 14
            }

            // Auto-hide after 3 seconds
            Timer {
                id: errorTimer
                interval: 3000
                onTriggered: errorPopup.visible = false
            }
        }
    }

    // ============== LISTEN TO C++ SIGNALS ==============
    Connections {
        target: calc

        function onErrorOccurred(errorMessage) {
            errorText.text = errorMessage
            errorPopup.visible = true
            errorTimer.start()
        }
    }
}
