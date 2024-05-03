import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    Item {
        id: stateArea

        width: parent.width
        height: parent.height - Theme.itemSizeSmall
        visible: networkListener.hasMobileData && provider.dataVolume > 0

        ProgressCircle {
            id: progress

            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }

            property real size: Math.min(parent.width, parent.height)
                                - 2 * Theme.horizontalPageMargin

            inAlternateCycle: true

            width: size
            height: size
            visible: true

            value: provider.usedDataVolume / provider.dataVolume
            borderWidth: Theme.paddingSmall
        }

        Column {
            id: data

            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: humanizeFileSize(provider.dataVolume - provider.usedDataVolume)
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeLarge
            }
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: humanizeUntilDate(provider.until)
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeExtraSmall
            }
        }

        Label {
            id: lastUpdateLabel
            anchors {
                top: progress.bottom
                topMargin: Theme.paddingSmall
                horizontalCenter: parent.horizontalCenter
            }

            text: qsTr("N/A")
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeSmall

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
                onDataChanged: {
                    lastUpdateLabel.text = humanizeTimeDiff(provider.lastUpdate)
                }
            }
        }
    }

    Label {
        visible: !networkListener.hasMobileData
        width: parent.width
        height: parent.height

        text: qsTr("No mobile data active")
        color: Theme.highlightColor
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    CoverActionList {
        id: coverAction
        enabled: networkListener.hasMobileData

        CoverAction {
            iconSource: "image://theme/icon-cover-sync"
        }
    }
}
