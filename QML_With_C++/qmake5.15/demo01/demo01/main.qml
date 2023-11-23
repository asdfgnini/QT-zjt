import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Interaction 1.0

ApplicationWindow {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Button{
        x:100
        width: 50
        height: 50
        text: "clicked"
        highlighted: true
        onClicked: {
            console.log("ckicked")
        }
    }

    Text {
        id: text01
        text: number("0")
    }

    Timer{
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            text01.text += 1
        }
    }


    Interaction{
        id:interaction
    }

}
