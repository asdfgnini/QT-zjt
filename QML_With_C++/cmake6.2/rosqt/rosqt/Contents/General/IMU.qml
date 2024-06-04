import QtQuick 2.9
import QtQuick.Controls 2.2
import TaoQuick 1.0

Item {
    anchors.fill: parent

    property string value: ""


    Timer{
        id:timer_Buttons
        interval: 200
        repeat: true
        onTriggered: {
            // console.log("触发")
            if(inter.value === "")
            {
                value = "...."
            }
            else
            {
                value = inter.value
                console.log(inter.value)
            }
        }
    }
    Column{
        anchors.centerIn: parent
        spacing: 20
        Row{
            spacing: 10
            CusLabel {
                text: qsTr("加速度:")
                wrapMode: Label.WordWrap
                // width: 400
                font.pixelSize: 20
            }

            CusLabel {
                text: qsTr(value)
                wrapMode: Label.WordWrap
                color: "red"
                // width: 400
                font.pixelSize: 20
            }
            CusLabel {
                text: qsTr(value)
                wrapMode: Label.WordWrap
                color: "red"
                // width: 400
                font.pixelSize: 20
            }
            CusLabel {
                text: qsTr(value)
                wrapMode: Label.WordWrap
                color: "red"
                // width: 400
                font.pixelSize: 20
            }
        }
        Row{
            spacing: 10
            CusLabel {
                text: qsTr("角速度:")
                wrapMode: Label.WordWrap
                // width: 400
                font.pixelSize: 20
            }

            CusLabel {
                text: qsTr(value)
                wrapMode: Label.WordWrap
                color: "red"
                // width: 400
                font.pixelSize: 20
            }
            CusLabel {
                text: qsTr(value)
                wrapMode: Label.WordWrap
                color: "red"
                // width: 400
                font.pixelSize: 20
            }
            CusLabel {
                text: qsTr(value)
                wrapMode: Label.WordWrap
                color: "red"
                // width: 400
                font.pixelSize: 20
            }
        }
    }

    Component.onCompleted: {
        // console.log("OK")
        timer_Buttons.start()
    }


}
