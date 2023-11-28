import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        anchors.fill: parent
        color: "grey"

        Image {
            id: image
            x:(root.width - image.width) / 2
            y:40
            source: "qrc:/32x32/cart.png"

        }

        Text {
            id: text
            horizontalAlignment: Text.AlignHCenter
            width: root.width   //设置width属性，horizontalAlignment属性才会生效
            y:image.y + image.height + 10
            color: "white"
            text: qsTr("购物车")
        }
    }
}
