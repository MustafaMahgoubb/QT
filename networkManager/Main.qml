import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ApplicationWindow {
    id: appWindowID
    visible: true
    title: qsTr("Network Manager")

    header:  TabBar {
        id: bar
        width: parent.width

        TabButton {
            text: qsTr("HomeTab")

        }

        TabButton {
            text: qsTr("Network")
            onClicked: {
                wifiManager.scan()
            }
        }
        TabButton {
            text: qsTr("Bluetooth")
        }
    }

    StackLayout {
        id : stackID
        anchors.fill: parent
        currentIndex: bar.currentIndex
        Item {
            id: homeTab
            Rectangle {
                anchors.fill: parent
                color: '#2b2e2d'

                RowLayout {
                    id: buttonsList
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 30
                    spacing: parent.width / 4

                    Button {
                        id: wifiButton
                        Layout.preferredHeight: 80
                        Layout.preferredWidth: 80
                        background: Rectangle {
                            color: wifiButton.wifiState ? "#575624" : "transparent"
                            radius: 10

                        }
                        property bool wifiState: wifiManager.isEnabled()

                        onClicked: {
                            if (wifiState) {
                                wifiManager.disable()
                                networkModel.clear()
                            } else {
                                wifiManager.enable()
                            }
                            wifiState = wifiManager.isEnabled()
                        }

                        Image {
                            id: wifiImg
                            source: wifiButton.wifiState ? "qrc:/images/WIFI_OPENED" : "qrc:/images/WIFI_CLOSED"
                            anchors.fill: parent
                            anchors.margins: 10
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Button {
                        id: btButton
                        Layout.preferredHeight: 80
                        Layout.preferredWidth: 80
                        background: Rectangle {
                            color: btButton.btState ? "#575624" : "transparent"
                            radius: 10
                        }

                        property bool btState: false

                        onClicked: {
                            btState = !btState
                        }
                        Image {
                            id: btImg
                            source: btButton.btState ? "qrc:/images/BLUETOOTH_OPENED" : "qrc:/images/BLUETOOTH_CLOSED"
                            anchors.fill: parent
                            anchors.margins: 10
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                }
            }
        }
        Item {
            id: networkTab
            Rectangle {
                anchors.fill: parent
                color: '#2b2e2d'

                // Listen for networksFound signal
                Connections {
                    target: wifiManager
                    function onNetworksFound(networks) {
                        console.log("Networks received:", networks)
                        networkModel.clear()
                        for (var i = 0; i < networks.length; i++) {
                            networkModel.append({"ssid": networks[i]})
                        }
                    }
                }

                ColumnLayout {
                    id: networkListLayout
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 10

                    // Scan Button
                    Button {
                        id: scanButton
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        text: "Scan Networks"

                        background: Rectangle{
                            color: "#575624"
                            radius: 10
                        }

                        onClicked: {
                            wifiManager.scan()
                            // Removed manual getNetworks() call
                            // Signal will handle it automatically!
                        }
                    }

                    // Network List
                    ListView {
                        id: networkListView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 10
                        clip: true

                        model: ListModel {
                            id: networkModel
                        }

                        delegate: Button {
                            width: networkListView.width
                            height: 50

                            background: Rectangle {
                                color: "#3d4140"
                                border.color: "#ffffff"
                                border.width: 1
                                radius: 5
                            }

                            contentItem: Text {
                                text: model.ssid
                                color: "#ffffff"
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }

                            onClicked: {
                                console.log("Selected network:", model.ssid)
                                var path = wifiManager.findSavedConnection(model.ssid)
                                // Already Saved Network
                                if (path !== "")
                                {
                                    // Saved network -> connect directly
                                    console.log("Connecting to saved network:", model.ssid)
                                    wifiManager.activate(path)
                                }
                                else
                                {
                                    console.log("New Network please Add Password")
                                    passwordDialog.networkName = model.ssid
                                    passwordDialog.open()
                                }
                            }
                        }
                    }
                }
                Dialog {
                    id: passwordDialog
                    title: "Enter Password"
                    modal: true
                    anchors.centerIn: parent

                    property string networkName: ""

                    ColumnLayout {
                        spacing: 10

                        Text {
                            text: "Network: " + passwordDialog.networkName
                            color: "#ffffff"
                        }

                        TextField {
                            id: passwordField
                            placeholderText: "Password"
                            echoMode: TextInput.Password
                            Layout.preferredWidth: 200
                        }

                        RowLayout {
                            spacing: 10

                            Button {
                                text: "Cancel"
                                onClicked: passwordDialog.close()
                            }

                            Button {
                                text: "Connect"
                                onClicked: {
                                    wifiManager.connectTo(passwordDialog.networkName, passwordField.text)
                                    passwordField.text = ""
                                    passwordDialog.close()
                                }
                            }
                        }
                    }
                }
            }
        }
        Item {
            id: bluetoothTab
        }
    }
}
