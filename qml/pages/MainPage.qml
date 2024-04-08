import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: page.width
            x: Theme.horizontalPageMargin
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Data Meter")
            }

            Label {
                text: provider.passName
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraSmall
            }
            Label {
                text: qsTr("Error: ") + provider.errorString
                color: Theme.secondaryHighlightColor
            }
            Label {
                id: lastUpdateLabel
                text: "-"
                color: Theme.secondaryHighlightColor

                Timer {
                    interval: 1000 * 60
                    repeat: true
                    triggeredOnStart: true
                    running: page.status === PageStatus.Active
                    onTriggered: {
                        lastUpdateLabel.text = humanizeTimeDiff(provider.lastUpdate)
                    }
                }

                Connections {
                    target: provider
                    onUpdate: {
                        lastUpdateLabel.text = humanizeTimeDiff(provider.lastUpdate)
                    }
                }
            }

            Label {
                text: qsTr("Next update: ") + provider.nextUpdate
                color: Theme.secondaryHighlightColor
            }

            ProgressCircle {
                id: progress

                property real size: Math.min(page.width, page.height)
                                    - 2 * Theme.horizontalPageMargin

                inAlternateCycle: true

                anchors.horizontalCenter: parent.horizontalCenter
                width: size
                height: size
                visible: true

                value: provider.usedDataVolume / provider.dataVolume
                borderWidth: Theme.paddingMedium

                Column {
                    anchors {
                        horizontalCenter: progress.horizontalCenter
                        verticalCenter: progress.verticalCenter
                    }

                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("Used: ") + humanizeFileSize(provider.usedDataVolume)
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraLarge
                    }
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("Total: ") + humanizeFileSize(provider.dataVolume)
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraLarge
                    }
                }
            }

        }
    }
}
