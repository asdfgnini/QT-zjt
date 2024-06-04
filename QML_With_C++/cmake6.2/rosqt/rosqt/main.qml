import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4


import TaoQuick 1.0

import "./Qml/Dialog"
import "./Qml/Pane"

ApplicationWindow {
    id: rootBackground
    width: 1440
    height: 960
    visible: true //设置可见性
    //设置背景图片
    CusImage{
        id: bgImg
        source: "qrc:/Image/Window/flower.jpg"
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        opacity: 0.1
    }
    //计算当前屏幕的刷新率
    CusFPS {
        anchors {
            right: parent.right
            top: parent.top
            rightMargin: 5
        }
    }
    //左边控制栏
    LeftPane {
        id: leftPane
        objectName: "leftPane"
        property real targetW: parent.width * 0.233
        width: targetW
        height: parent.height
        property bool isOpen: true
        x: isOpen ? 0 : -targetW - 4
        Behavior on x {
            NumberAnimation { duration: 350}
        }
        onLoadHome: function() {
            rightPane.source = rightPane.homeUrl
        }
        onLoadContent: function(path) {
            rightPane.source = "qrc:/Contents/" + path
        }
    }
    //控制栏缩进控制
    CusButton {
        id:left_controlbtn
        objectName: "menuBtn"
        anchors {
            left: leftPane.right
            top: leftPane.top
            topMargin: 2
        }
        width: 32
        height: 32
        background:Rectangle {
            width:left_controlbtn.width
            height: left_controlbtn.height
            color: left_controlbtn.pressed ? CusConfig.controlBorderColor_pressed : (left_controlbtn.hovered ? CusConfig.controlBorderColor_hovered : CusConfig.controlColor)
            radius: left_controlbtn.width / 2
            CusImage {
                source: "qrc:/Image/Button/expand.png"
                anchors {
                    right: parent.right
                    rightMargin: 4
                    top: parent.top
                    topMargin: 4
                }
                rotation: leftPane.isOpen ? 90 : -90
                Behavior on rotation {
                    NumberAnimation {
                        duration: 200
                    }
                }
            }
        }
        onClicked: {
            leftPane.isOpen = !leftPane.isOpen
        }
    }
    //左边和右边分隔栏
    Rectangle {
        width: 1
        anchors {
            top: leftPane.top
            bottom: leftPane.bottom
            right: leftPane.right
        }
        color: CusConfig.controlBorderColor
    }
    //右边展示栏
    RightPane {
        id: rightPane
        objectName: "contentRect"
        anchors {
            left: leftPane.right
            leftMargin: 40
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }

    //本组件加载时运行ROS任务
    Component.onCompleted: {
        inter.start_ros()
    }

}
