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
    property int value: 0



    Button{
        id:btn
        x:100
        width: 50
        height: 50
        text: "clicked"
        highlighted: true
        onClicked: {
            interaction.test_slot()
        }
    }

    Text {
        id: text01
        font.pixelSize: 40
        anchors.centerIn: parent
        text: value
    }

    Timer{
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            value++;
        }
    }


    Interaction{
        id:interaction
    }


}
