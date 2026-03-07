import QtQuick
import QtMultimedia

Rectangle {
    id: splashRoot

    signal splashFinished()

    color: "#000000"

    Video {
        id: splashVideo
        anchors.fill: parent

        source: "qrc:/videos/SPLASH_SCREEN"

        fillMode: VideoOutput.PreserveAspectCrop
        volume: 0.0

        onPositionChanged: {
                    if (duration > 0 && position >= duration - 100) {
                        splashFinished()
                    }
                }

                Component.onCompleted: {
                    play()
                }
    }

}
