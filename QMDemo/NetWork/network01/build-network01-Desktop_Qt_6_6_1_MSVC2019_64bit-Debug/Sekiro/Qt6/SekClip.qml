import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import Sekiro

SekRectangle
{
    id:control
    color: "#00000000"
    layer.enabled: !SekTools.isSoftware()
    layer.effect: OpacityMask{
        maskSource: ShaderEffectSource{
            sourceItem: SekRectangle{
                radius: control.radius
                width: control.width
                height: control.height
            }
        }
    }
}



