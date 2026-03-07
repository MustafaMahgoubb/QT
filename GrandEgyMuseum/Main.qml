import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root

    property string app_name: "Grand Egyptian Museum"

    visible: true
    title: app_name

    readonly property int baseWidth: 1920
    readonly property int baseHeight: 1080

    property int main_currWidth: 1280
    property int main_currHeight: 720

    width: main_currWidth
    height: main_currHeight

    minimumWidth: 800
    minimumHeight: 600

    color: "#1a1a2e"

    // Global StackView
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "screensQml/SplashScreen.qml"

        Component.onCompleted:
        {
            console.log("Loaded SplashScreen")
        }
    }

    // Connection to handle signals from current item
    Connections {
        target: stackView.currentItem
        ignoreUnknownSignals: true

        function onSplashFinished() {
            stackView.replace("screensQml/HomeScreen.qml")
        }

        function onOpenPage(pageSource) {
            stackView.push(pageSource)
        }

        function onGoBack() {
            stackView.pop()
        }
    }
}
