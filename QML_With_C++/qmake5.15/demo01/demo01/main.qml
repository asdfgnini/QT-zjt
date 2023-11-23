import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Button{
        anchors.centerIn: parent
        text: "clicked"
        onClicked: {
            console.log("ckicked")
        }
    }

}
