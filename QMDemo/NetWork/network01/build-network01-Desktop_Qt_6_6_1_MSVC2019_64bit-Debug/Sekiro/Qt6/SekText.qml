import QtQuick
import QtQuick.Controls
import Sekiro

Text {
    property color textColor: SekTheme.fontPrimaryColor
    id:text
    color: textColor
    renderType: SekTheme.nativeText ? Text.NativeRendering : Text.QtRendering
    font: SekTextStyle.Body
}
