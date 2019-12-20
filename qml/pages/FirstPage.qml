import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            x: Theme.horizontalPageMargin
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Data Meter")
            }

            Label {
                text: "Pass-Name: " + provider.passName
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraSmall
            }
            Label {
                text: "Error: " + provider.errorString
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
                    running: true
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
                text: "Nächste Aktuallisierung: " + provider.nextUpdate
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
                        text: "Used: " + humanizeFileSize(provider.usedDataVolume)
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraLarge
                    }
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Total: " + humanizeFileSize(provider.dataVolume)
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraLarge
                    }
                }
            }

        }
    }
}
