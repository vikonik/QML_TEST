import QtQuick 2.0
import QtQuick.Controls 2.15
import StyleSetting 1.0

CustomButton {
    id: button_ScanID
    x:132-17
    width: 161
    height: 42
    color: "transparent"

    defaultImage: "qrc:/Image/buttonsScanID/buttonScanID_default.png"
    hoverImage: "qrc:/Image/buttonsScanID/buttonScanID_hover.png"
    pressedImage: "qrc:/Image/buttonsScanID/buttonScanID_preset.png"

    onClicked: console.log("button buttonsScanID clicked")
}
