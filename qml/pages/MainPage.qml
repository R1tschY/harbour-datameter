import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    function updateDisplay() {
        lastUpdateLabel.text = qsTr("Last update: %1").arg(humanizeTimeDiff(provider.lastUpdate))
    }

    onStatusChanged: page.updateDisplay()

    Timer {
        interval: 1000 * 60
        repeat: true
        triggeredOnStart: true
        running: page.status === PageStatus.Active
        onTriggered: page.updateDisplay()
    }

    Connections {
        target: provider
        onDataChanged: page.updateDisplay()
    }

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: page.width

            PageHeader {
                title: qsTr("Data Meter")
            }

            ViewPlaceholder {
                visible: !!provider.errorString
                text: qsTr("Error: %1").arg(provider.errorString)
            }

            ViewPlaceholder {
                visible: !networkListener.hasMobileData
                text: qsTr("No mobile data active")
            }

            Column {
                width: page.width
                spacing: Theme.paddingLarge

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: provider.passName
                    font.pixelSize: Theme.fontSizeLarge
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("%1 of %2").arg(humanizeFileSize(provider.dataVolume - provider.usedDataVolume)).arg(humanizeFileSize(provider.dataVolume))
                    font.pixelSize: Theme.fontSizeExtraLarge
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("remaining for %1").arg(humanizeUntilDate(provider.until))
                }

                Label {
                    text: " "
                    height: Theme.paddingLarge
                }

                Label {
                    id: lastUpdateLabel

                    x: Theme.horizontalPageMargin
                    color: Theme.secondaryColor
                }
            }
        }
    }
}
