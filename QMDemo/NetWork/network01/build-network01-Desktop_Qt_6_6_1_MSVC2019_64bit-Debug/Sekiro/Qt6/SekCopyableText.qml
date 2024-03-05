import QtQuick
import QtQuick.Controls
import Sekiro

TextEdit {
    property color textColor: SekTheme.dark ? SekColors.White : SekColors.Grey220
    id:control
    color: textColor
    readOnly: true
    activeFocusOnTab: false
    activeFocusOnPress: false
    renderType: SekTheme.nativeText ? Text.NativeRendering : Text.QtRendering
    padding: 0
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    selectByMouse: true
    selectedTextColor: color
    bottomPadding: 0
    selectionColor: SekTools.colorAlpha(SekTheme.primaryColor,0.5)
    font:SekTextStyle.Body
    onSelectedTextChanged: {
        control.forceActiveFocus()
    }
    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.IBeamCursor
        acceptedButtons: Qt.RightButton
        onClicked: control.echoMode !== TextInput.Password && menu.popup()
    }
    SekTextBoxMenu{
        id:menu
        inputItem: control
    }
}
