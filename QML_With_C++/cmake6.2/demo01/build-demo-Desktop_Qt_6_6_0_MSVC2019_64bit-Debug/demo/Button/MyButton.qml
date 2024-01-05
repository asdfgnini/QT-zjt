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


    }

}
