import QtQuick
import QtQuick.Controls

import Interaction 1.0

import "./MyButton"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ToolButton{
        icon.source: "qrc:/demo/images/32x32/cart.png"
        anchors.centerIn: parent
    }


    Interaction{
        id:interaction
    }

    MyButton{
        id:mybutton
    }

    Component.onCompleted: {
        interaction.test();
    }
}
