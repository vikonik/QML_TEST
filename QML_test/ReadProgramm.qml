import QtQuick 2.0

Rectangle{
    id: readProgramm_buttons
    width: 223
    height: 42
    color: "transparent"

    CustomButton {
        id: button_Read
        x:0
        width: 108
        height: 42
        color: "transparent"

        defaultImage: "qrc:/Image/buttonReadProgramm/buttonRead_default.png"
        hoverImage: "qrc:/Image/buttonReadProgramm/buttonRead_hover.png"
        pressedImage: "qrc:/Image/buttonReadProgramm/buttonRead_preset.png"

        onClicked: console.log("Disconnect button clicked")
    }

    CustomButton {
        id: button_Programm
        x:132-17
        width: 108
        height: 42
        color: "transparent"

        defaultImage: "qrc:/Image/buttonReadProgramm/buttonPriogramm_default.png"
        hoverImage: "qrc:/Image/buttonReadProgramm/buttonPriogramm_hover.png"
        pressedImage: "qrc:/Image/buttonReadProgramm/buttonPriogramm_preset.png"

        onClicked: console.log("Disconnect button clicked")
    }
}
