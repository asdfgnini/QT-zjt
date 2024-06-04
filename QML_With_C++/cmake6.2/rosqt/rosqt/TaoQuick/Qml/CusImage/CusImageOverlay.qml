import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15

import TaoQuick 1.0

import ".."
import "../.."

Item {
    id: cusImage

    property string imgNormal

    property bool imgHovered: hoverHandler.hovered
    property bool imgPressed
    property bool imgDisabled

    property color colorNormal: CusConfig.imageColor
    property color colorHovered: CusConfig.imageColor_hovered
    property color colorPressed: CusConfig.imageColor_pressed
    property color colorDisable: CusConfig.imageColor_disabled
    implicitWidth: baseImage.width
    implicitHeight: baseImage.height
    property alias color: overlay.imageColor
	property alias imageItem: baseImage
    CusImage {
        id: baseImage
        source: imgNormal
        smooth: true
        visible: false
    }
    CusColorOverlay {
        id: overlay
        width: baseImage.width
        height: baseImage.height
        anchors.centerIn: parent

        source : baseImage
        imageColor: {
            if (imgDisabled) {
                return colorDisable
            } else if (imgPressed) {
                return colorPressed
            } else if (imgHovered) {
                return colorHovered
            } else {
                return colorNormal
            }
        }
    }
    HoverHandler {
        id: hoverHandler
    }
}
