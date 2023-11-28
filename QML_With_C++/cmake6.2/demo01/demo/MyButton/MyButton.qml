import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {

    RowLayout {
        Button {
            text: "Ok"
            onClicked: model.submit()
        }
        Button {
            text: "Cancel"
            onClicked: model.revert()
        }
        ToolButton{
            icon.source: "qrc:/demo/images/32x32/cloud.png"
            onClicked: {
                console.log("资源文件加载OK")
            }
        }
    }
}
