import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15

import ".."
import "../.."

ShaderEffect {
    id: cusColorOverlay
    property Image source
    property color imageColor
    fragmentShader: CusConfig.shaderPath + "cusColorOverlay.frag.qsb"
}
