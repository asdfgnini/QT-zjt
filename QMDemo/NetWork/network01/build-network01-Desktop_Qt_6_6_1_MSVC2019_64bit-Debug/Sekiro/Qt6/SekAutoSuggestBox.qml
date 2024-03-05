import QtQuick
import QtQuick.Controls
import Sekiro

SekTextBox{
    property var items:[]
    property string emptyText: "没有找到结果"
    property int autoSuggestBoxReplacement: SekentIcons.Search
    property var window : Window.window
    signal itemClicked(var data)
    signal handleClicked
    id:control
    Component.onCompleted: {
        loadData()
    }
    QtObject{
        id:d
        property bool flagVisible: true
    }
    onActiveFocusChanged: {
        if(!activeFocus){
            control_popup.visible = false
        }
    }
    Popup{
        id:control_popup
        y:control.height
        focus: false
        padding: 0
        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from:0
                to:1
                duration: SekTheme.enableAnimation ? 83 : 0
            }
        }
        contentItem: SekRectangle{
            radius: [4,4,4,4]
            SekShadow{
                radius: 4
            }
            color: SekTheme.dark ? Qt.rgba(51/255,48/255,48/255,1) : Qt.rgba(248/255,250/255,253/255,1)
            ListView{
                id:list_view
                anchors.fill: parent
                clip: true
                boundsBehavior: ListView.StopAtBounds
                ScrollBar.vertical: SekScrollBar {}
                header: Item{
                    width: control.width
                    height: visible ? 38 : 0
                    visible: list_view.count === 0
                    SekText{
                        text:emptyText
                        anchors{
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 10
                        }
                    }
                }
                delegate:SekControl{
                    id:item_control
                    height: 38
                    width: control.width
                    onClicked:{
                        handleClick(modelData)
                    }
                    background: Rectangle{
                        SekFocusRectangle{
                            visible: item_control.activeFocus
                            radius:4
                        }
                        color:  {
                            if(hovered){
                                return SekTheme.dark ? Qt.rgba(63/255,60/255,61/255,1) : Qt.rgba(237/255,237/255,242/255,1)
                            }
                            return SekTheme.dark ? Qt.rgba(51/255,48/255,48/255,1) : Qt.rgba(0,0,0,0)
                        }
                    }
                    contentItem: SekText{
                        text:modelData.title
                        leftPadding: 10
                        rightPadding: 10
                        verticalAlignment : Qt.AlignVCenter
                    }
                }
            }
        }
        background: Item{
            id:container
            implicitWidth: control.width
            implicitHeight: 38*Math.min(Math.max(list_view.count,1),8)
        }
    }
    onTextChanged: {
        loadData()
        if(d.flagVisible){
            var pos = control.mapToItem(null, 0, 0)
            if(window.height>pos.y+control.height+container.implicitHeight){
                control_popup.y = control.height
            } else if(pos.y>container.implicitHeight){
                control_popup.y = -container.implicitHeight
            } else {
                control_popup.y = window.height-(pos.y+container.implicitHeight)
            }
            control_popup.visible = true
        }
    }
    function handleClick(modelData){
        control_popup.visible = false
        control.itemClicked(modelData)
        updateText(modelData.title)
    }
    function updateText(text){
        d.flagVisible = false
        control.text = text
        d.flagVisible = true
    }
    function loadData(){
        var result = []
        if(items==null){
            list_view.model = result
            return
        }
        items.map(function(item){
            if(item.title.indexOf(control.text)!==-1){
                result.push(item)
            }
        })
        list_view.model = result
    }
}
