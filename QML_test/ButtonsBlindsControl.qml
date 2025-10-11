//Управление шторой
import QtQuick 2.0
import QtQuick.Controls 2.12
import StyleSetting 1.0

Rectangle {
    id:_buttonsBlindsControl
    width: 223
    height: 129
    color: "transparent"

    property string buttonText: "Button"
    property string buttonId: ""
    property string resetImageDefault: ""
    property string resetImageHover: ""
    property string resetImagePteset: ""

    //Кнопка Reset
    Rectangle{
        id: button
        width: 69
        height: 22
        color: Style.backgroundColor
//        border.color: Style.borderColor
//        border.width: 1
        radius: 5


        CustomButton {
            id: button_Reset
            width: 96
            height: 22
            color: "transparent"

            defaultImage: resetImageDefault
            hoverImage: resetImageDefault
            pressedImage: resetImageDefault
            buttonId: _buttonsBlindsControl.buttonId+"button_Reset"
        }

//        Text{
//            id: text
//            text: buttonText
//            color: Style.buttonDefaultTextrColor
//            font.pixelSize: Style.fontSizeLabel

//            anchors.centerIn: parent
//        }

//        MouseArea {
//            anchors.fill: parent
//            hoverEnabled: true
//            cursorShape: Qt.PointingHandCursor

//            onReleased: {// Изображение при наведении
//                text.color = Style.buttonHoverBorderColor
//                parent.color = Style.buttonHoverBackgroundColor
//                parent.border.color = Style.buttonHoverBorderColor

//                console.log("buttonImage: onReleased")
//            }

//            onPressed: {
//                // Когда кнопка нажата
//                console.log("buttonImage: onPressed")
//                       // buttonId: _buttonsBlindsControl.buttonId+"Reset"
//                _buttonsBlindsControl.buttonClicked(button.buttonId)
//            }

//            onExited: {
//                // Когда мышка покидает кнопку
//                text.color = Style.buttonDefaultTextrColor
//                parent.color = Style.backgroundColor
//                parent.border.color = Style.borderColor

//                console.log("buttonImage: onExited")

//            }

//            onEntered: {
//                text.color = Style.buttonHoverBorderColor
//                parent.color = Style.buttonHoverBackgroundColor
//                parent.border.color = Style.buttonHoverBorderColor
//                console.log("buttonImage: onEntered")
//            }
//        }
    }

    Rectangle{//Чтобы сделать голубой фон за кнопками
        //   anchors.fill: parent
        color: "#56B0ED"
        radius: 5
        height: 100
        //spacing:50
        // Привязка к нижней границе родителя
        anchors.bottom: parent.bottom

        // Растягиваем вверх на еличину height
        anchors.left: parent.left
        anchors.right: parent.right

        Component.onCompleted: {
            onload: console.log("Row width:", width)
        }

        //****
        Column {
            width: 80
            height: parent.height
            spacing: 1  // Устанавливаем отступ между кнопками

            CustomButton {
                id: button_UP
                width: 80
                height: 50
                color: "transparent"

                defaultImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsUp_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsUp_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsUp_preset.png"
                buttonId: _buttonsBlindsControl.buttonId+"button_UP"
            }

            CustomButton {
                id: button_UpLeft
                width: 80
                height: 50
                color: "transparent"

                defaultImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsUpLeft_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsUpLeft_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsUpLeft_preset.png"
                buttonId: _buttonsBlindsControl.buttonId+"button_UpLeft"
            }
        }

        //***
        Column{
            width: 62
            height: parent.height
            x: parent.x + 80 + 1
            CustomButton{
                id: button_Stop
                width: 62
                height: parent.height + 1
                color: "transparent"

                defaultImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsStop_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsStop_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsStop_preset.png"
                buttonId: _buttonsBlindsControl.buttonId+"button_Stop"
                // onClicked: console.log("button_Stop clicked")
            }

        }

        Column{
            width: parent.width/3
            height: parent.height
            x: parent.x + 80 + 63 + 1
            spacing: 1
            CustomButton{
                id: button_Down
                width: 80
                height: 50
                color: "transparent"

                defaultImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsDown_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsDown_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsDown_preset.png"
                buttonId: _buttonsBlindsControl.buttonId+"button_Down"
                //  onClicked: console.log("button_Down clicked")


            }
            CustomButton{
                id: button_DownRight
                width: 80
                height: 50
                color: "transparent"

                defaultImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsDownRight_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsDownRight_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControl/buttonBlindsDownRight_preset.png"
                buttonId: _buttonsBlindsControl.buttonId+"button_DownRight"
                // onClicked: console.log("button_UpLeft clicked")
            }
        }
    }

}
