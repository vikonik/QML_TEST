import QtQuick 2.0

Rectangle{
    id: edet_buttons
    width: 223
    height: 72
    color: "transparent"

    Column {
            anchors.centerIn: parent
            spacing: 10 // Расстояние между рядами

            Row {
                spacing: 10 // Расстояние между кнопками в ряду

                CustomButton {
                    id: button_DefaultSetup
                    width: 138
                    height: 29
                    color: "transparent"
                    defaultImage: "qrc:/Image/buttonEbit/buttonDefaultSetup_default.png"
                    hoverImage: "qrc:/Image/buttonEbit/buttonDefaultSetup_hover.png"
                    pressedImage: "qrc:/Image/buttonEbit/buttonDefaultSetup_preset.png"
buttonId: "button_DefaultSetup"
                    onClicked: console.log("button_DefaultSetup clicked")

                }

                CustomButton {
                    id: button_Copy
                    width: 72
                    height: 29
                    color: "transparent"
                    defaultImage: "qrc:/Image/buttonEbit/buttonCopy_default.png"
                    hoverImage: "qrc:/Image/buttonEbit/buttonCopy_hover.png"
                    pressedImage: "qrc:/Image/buttonEbit/buttonCopy_preset.png"
buttonId: "button_Copy"
                    onClicked: console.log("button_DefaultSetup clicked")
                }


            }

            Row {
                spacing: 10 // Расстояние между кнопками в ряду

                CustomButton {
                    id: button_DownloadSetup
                    width: 138
                    height: 29
                    color: "transparent"
                    defaultImage: "qrc:/Image/buttonEbit/buttonDownloadSetup_default.png"
                    hoverImage: "qrc:/Image/buttonEbit/buttonDownloadSetup_hover.png"
                    pressedImage: "qrc:/Image/buttonEbit/buttonDownloadSetup_preset.png"
buttonId: "button_DownloadSetup"
                    onClicked: console.log("button_DefaultSetup clicked")
                }

                CustomButton {
                    id: button_Paste
                    width: 72
                    height: 29
                    color: "transparent"
                    defaultImage: "qrc:/Image/buttonEbit/buttonPaste_default.png"
                    hoverImage: "qrc:/Image/buttonEbit/buttonPaste_hover.png"
                    pressedImage: "qrc:/Image/buttonEbit/buttonPaste_preset.png"
buttonId: "button_Paste"
                    onClicked: console.log("button_DefaultSetup clicked")
                }
            }
        }


}
