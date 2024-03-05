import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import Sekiro

TextArea{
    signal commit(string text)
    property bool disabled: false
    property color normalColor: SekTheme.dark ?  Qt.rgba(255/255,255/255,255/255,1) : Qt.rgba(27/255,27/255,27/255,1)
    property color disableColor: SekTheme.dark ? Qt.rgba(131/255,131/255,131/255,1) : Qt.rgba(160/255,160/255,160/255,1)
    property color placeholderNormalColor: SekTheme.dark ? Qt.rgba(210/255,210/255,210/255,1) : Qt.rgba(96/255,96/255,96/255,1)
    property color placeholderFocusColor: SekTheme.dark ? Qt.rgba(152/255,152/255,152/255,1) : Qt.rgba(141/255,141/255,141/255,1)
    property color placeholderDisableColor: SekTheme.dark ? Qt.rgba(131/255,131/255,131/255,1) : Qt.rgba(160/255,160/255,160/255,1)
    property bool isCtrlEnterForNewline: false
    id:control
    enabled: !disabled
    color: {
        if(!enabled){
            return disableColor
        }
        return normalColor
    }
    font:SekTextStyle.Body
    wrapMode: Text.WrapAnywhere
    padding: 8
    leftPadding: padding+4
    renderType: SekTheme.nativeText ? Text.NativeRendering : Text.QtRendering
    selectedTextColor: color
    selectionColor: SekTools.colorAlpha(SekTheme.primaryColor,0.5)
    placeholderTextColor: {
        if(!enabled){
            return placeholderDisableColor
        }
        if(focus){
            return placeholderFocusColor
        }
        return placeholderNormalColor
    }
    selectByMouse: true
    width: 240
    background: SekTextBoxBackground{
        inputItem: control
    }
    Keys.onEnterPressed: (event)=> d.handleCommit(event)
    Keys.onReturnPressed:(event)=> d.handleCommit(event)
    QtObject{
        id:d
        function handleCommit(event){
            if(isCtrlEnterForNewline){
                if(event.modifiers & Qt.ControlModifier){
                    insert(control.cursorPosition, "\n")
                    return
                }
                control.commit(control.text)
            }else{
                if(event.modifiers & Qt.ControlModifier){
                    control.commit(control.text)
                    return
                }
                insert(control.cursorPosition, "\n")
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.IBeamCursor
        acceptedButtons: Qt.RightButton
        onClicked: {
            if(control.echoMode === TextInput.Password){
                return
            }
            if(control.readOnly && control.text === ""){
                return
            }
            menu.popup()
        }
    }
    SekTextBoxMenu{
        id:menu
        inputItem: control
    }
}
