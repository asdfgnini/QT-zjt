import QtQuick
import QtQuick.Controls
import Sekiro

Text {
    property int iconSource
    property int iconSize: 20
    property color iconColor: SekTheme.dark ? "#FFFFFF" : "#000000"
    id:control
    font.family: "Segoe Fluent Icons"
    font.pixelSize: iconSize
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    color: iconColor
    text: (String.fromCharCode(iconSource).toString(16))

}
