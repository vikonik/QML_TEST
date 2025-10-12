//Кнопки группавого управления жалюзи
import QtQuick 2.0
import StyleSetting 1.0


Rectangle {
    width: 223
    height: 42
    color: "transparent"
//property var buttonHandler
    Row {
        anchors.fill: parent
        spacing: 1  // Добавляем отступ между элементами в Row

        Rectangle { // Кнопки слева
            id: btFromLeft
            width: 68
            height: parent.height
            radius: 5
            color: Style.buttonGroupConrolBackgroundColor

            CustomButton{
                id: buttonGroupUp
                width: 33
                height: 42
                anchors.left: parent.left

                defaultImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupUp_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupUp_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupUp_preset.png"
                buttonId: "buttonGroupUp"
                //onClicked: console.log("button_UP clicked")
            }

            CustomButton{
                id: buttonGroupDown
                width: 33
                height: 42
                anchors.right:  parent.right

                defaultImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupDown_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupDown_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupDown_preset.png"
                buttonId: "buttonGroupDown"
                //onClicked: console.log("button_UP clicked")
            }

        }

        Rectangle { // Поле ввода
            width: 79
            height: parent.height
            radius: 8

            color: Style.backgroundColor
            border.color: Style.borderColor
            border.width: 2

            TextInput {
                id:groupMouvingVal
                anchors.fill: parent
                anchors.margins: 5
                text: "1000"
                font.pixelSize: Style.fontSizeValue
                color: Style.fontColorValue
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                //onTextChanged: console.log("TextInput: ", text)
                // Обновляем свойство в C++ при изменении текста
                onTextChanged: {
                    if (buttonHandler && buttonHandler.groupMovingValue !== text) {
                        buttonHandler.groupMovingValue = text;
                    }
                }
            }

        }

        Rectangle { // Кнопки слева
            id: btFromRight
            width: 68
            height: parent.height
            radius: 5
            color: Style.buttonGroupConrolBackgroundColor

            CustomButton{
                id: buttonGroupUpLeft
                width: 33
                height: 42
                anchors.left: parent.left

                defaultImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupUpLeft_defaut.png"
                hoverImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupUpLeft_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupUpLeft_preset.png"
                buttonId: "buttonGroupUpLeft"
                onClicked: console.log("button_UP clicked")
            }

            CustomButton{
                id: buttonGroupDownRight
                width: 33
                height: 42
                anchors.right:  parent.right

                defaultImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupDownRight_default.png"
                hoverImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupDownRight_hover.png"
                pressedImage: "qrc:/Image/buttonsBlindsControlGroup/buttonBlindsGroupDownRight_preset.png"

                 buttonId: "buttonGroupDownRight"
                 onClicked: console.log("button_UP clicked")
            }

        }

    }

    Connections {
        target: buttonHandler
        onGroupMovingValueChanged: {
            if (groupMouvingVal.text !== buttonHandler.groupMovingValue) {
                groupMouvingVal.text = buttonHandler.groupMovingValue;
            }
        }

}
}
