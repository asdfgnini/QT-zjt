import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import Sekiro



Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property string str: ""

    SekArea{
        id:flick_rect
        width: 300; height: 200;
        border{
            color: "steelblue"
            width: 2
        }
        Flickable {
            id: flick
            anchors.fill: parent
            contentWidth: edit.contentWidth
            contentHeight: edit.contentHeight
            ScrollBar.vertical: SekScrollBar {}
            clip: true

            function ensureVisible(r)
            {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                    contentX = r.x+r.width-width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                    contentY = r.y+r.height-height;
            }

            SekCopyableText {
                id: edit
                width: flick.width
                focus: true
                wrapMode: TextEdit.Wrap
                onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
            }
        }
    }

    SekTextBox{
        id:ip_text
        anchors.top:flick_rect.bottom
        anchors.topMargin: 20
        placeholderText: "输入服务器ip"
        text: "192.168.0.103"
    }

    SekTextBox{
        id:port_text
        anchors.top:ip_text.bottom
        anchors.topMargin: 20
        placeholderText: "输入端口号"
        text:"8000"
    }


    SekiroButton{
        id:connect_btn
        anchors.top: port_text.bottom
        anchors.topMargin : 20
        text: "连接服务器"
        onClicked: {
            inter.connt(ip_text.text,port_text.text)
            console.log(ip_text.text,port_text.text)
        }
        Timer{
            id:connt_timer
            interval: 200
            repeat: true
            onTriggered: {
                if(inter.state() === true)
                {
                    connect_btn.text = "断开服务器"
                }
                else
                {
                    connect_btn.text = "连接服务器"
                }
            }
        }

        Component.onCompleted: {
            connt_timer.start()
        }
    }

    SekiroButton{
        id:send_btn
        anchors.top: connect_btn.top
        anchors.left: connect_btn.right
        anchors.leftMargin : 10
        text: "发送消息"
        onClicked: {
            inter.send(hex_btn.checked)
        }
    }

    SekiroButton{
        id:clear_btn
        anchors.left: flick_rect.right
        anchors.leftMargin : 20
        text: "清空"
        onClicked: {
            edit.clear()
        }
    }

    SekToggleSwitch{
        id:hex_btn
        anchors.left: clear_btn.left
        anchors.top :clear_btn.bottom
        anchors.topMargin: 10
        text: "Hex发送"

    }
    SekToggleSwitch{
        id:hex_btn2
        anchors.left: hex_btn.left
        anchors.top :hex_btn.bottom
        anchors.topMargin: 10
        text: "Hex接收"
        onClicked: {
            inter.setstate(hex_btn2.checked)
        }
    }

    Connections{
        id:connect
        target: inter
        function onSignvalue(value)
        {
            console.log(value)
            str = value
            edit.append(value)
        }
    }
}
