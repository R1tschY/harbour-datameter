import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    function humanizeFileSize(size) {
        var units = ['B', 'kB', 'MB', 'GB', 'TB']
        var dim = (size !== 0)
            ? Math.min(Math.floor(Math.log(Math.abs(size)) / Math.log(1024)), units.length - 1)
            : 0
        if (dim !== 0) {
            return (size / Math.pow(1024, dim)).toFixed(1) + "\u202F" + units[dim]
        } else {
            return size + "\u202F" + units[0]
        }
    }

    function humanizeTimeDiff(date) {
        var diff = date - new Date();
        var minutes = Math.floor(diff / (1000 * 60))

        if (minutes === 0) {
            return qsTr("just now")
        } else if (minutes < 0) {
            return qsTr("%1\u202Fmin ago", "", -minutes).arg(-minutes)
        } else {
            return qsTr("in %1\u202Fmin", "", minutes).arg(minutes)
        }
    }


    initialPage: Component { MainPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}
