import QtQuick 2.0
import StyleSetting 1.0


Item {
    id: panelInfo
    width: 223
    height: 134
//    property string serialText: ""
//    property string minAngleText: ""
//    property string typeText: ""
//    property string activationDateText: ""

    // Прямое использование свойств контроллера
    property string serialText: tableController.serialText
    property string minAngleText: tableController.minAngleText
    property string typeText: tableController.typeText
    property string activationDateText: tableController.activationDateText
  //  color: "transparent"
Rectangle{
    id: rowText_1
    width: parent.width
    height: Style.fontSizeLabel
    color: "transparent"

    Text{
        //id: labelComPort
        text: "Serial"
        color: Style.fontColorLabel
        font.family: Style.fontLabel
        font.pixelSize: Style.fontSizeLabel

    }

    Text{
       // id: labelComPort
        text: "Min Angle"
        color: Style.fontColorLabel
        font.family: Style.fontLabel
        font.pixelSize: Style.fontSizeLabel
        anchors.left: parent.left
        anchors.leftMargin: 109

    }
}

        Rectangle {
            id: roundedRectangle_1
            width: 222
            height: 45
            anchors.top: rowText_1.bottom
            anchors.topMargin: 5
            color: "transparent"//transparent
            radius: 5 // Скругленные углы
            border.color: Style.borderColor
            border.width: 2

            Image{
                source: "qrc:/Image/panelInfo/icon_cube_yellow.png" // Путь к изображению стрелки
                width: 20
                height: 22
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 5
            }

//            Text{
//                id: serial_ID
//                text:serialText
//                color: Style.fontColorValue
//                font.family: Style.fontValue
//                font.pixelSize: Style.fontSizeValue
//                anchors.left: parent.left
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.margins: 35
//            }

            TextInput {
                id: serial_ID
                text: serialText
                color: Style.fontColorValue
                font.family: Style.fontValue
                font.pixelSize: Style.fontSizeValue
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 35

                // Настройки поля ввода
                //focus: true                     // автоматически ставит фокус (по желанию)
                selectByMouse: true             // позволяет выделять текст мышью
                cursorVisible: true             // видимый курсор
                inputMethodHints: Qt.ImhNone    // можно менять для цифр, паролей и т.д.
                //background: null                 // прозрачный фон, если нужен
                // Обработка нажатия Enter
                onAccepted: {
                    // Вызываем метод контроллера для обновления значения
                    tableController.updateSerialValue(text)
                }

                // Обновляем свойство при изменении текста
                onTextChanged: {
                    //serialText = text
                }
            }

            // Полоса в центре
            Rectangle {
                id: verticalStripe
                width: 2 // Ширина полосы
                height: parent.height // Высота полосы с отступами
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: Style.borderColor
                //radius: 5 // Скругленные углы для полосы

                Image{
                    id: image_minAngle
                    source: "qrc:/Image/panelInfo/icon_angle.png" // Путь к изображению стрелки
                    width: 20
                    height: 22
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 5
                }

                Text{
                    id: minAngle
                    text:minAngleText
                    color: Style.fontColorValue
                    font.family: Style.fontValue
                    font.pixelSize: Style.fontSizeValue
                    anchors.left: image_minAngle.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 5
                }
            }
        }

 /*****************/
        Rectangle{
            id: rowText_2
            width: parent.width
            height: Style.fontSizeLabel
            color: "transparent"
            anchors.top: roundedRectangle_1.bottom
            anchors.topMargin: 10

            Text{
                //id: labelComPort
                text: "Type"
                color: Style.fontColorLabel
                font.family: Style.fontLabel
                font.pixelSize: Style.fontSizeLabel

            }

            Text{
               // id: labelComPort
                text: "Data activation"
                color: Style.fontColorLabel
                font.family: Style.fontLabel
                font.pixelSize: Style.fontSizeLabel
                anchors.left: parent.left
                anchors.leftMargin: 109

            }
        }

                Rectangle {
                    id: roundedRectangle_2
                    width: 222
                    height: 45
                    anchors.top: rowText_2.bottom
                    anchors.topMargin: 5
                    color: "transparent"//transparent
                    radius: 5 // Скругленные углы
                    border.color: Style.borderColor
                    border.width: 2

                    Text{
                        id: type
                        text:typeText
                        color: Style.fontColorValue
                        font.family: Style.fontValue
                        font.pixelSize: Style.fontSizeValue
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 35
                    }

                    // Полоса в центре
                    Rectangle {
                        id: verticalStripe_2
                        width: 2 // Ширина полосы
                        height: parent.height // Высота полосы с отступами
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Style.borderColor
                        //radius: 5 // Скругленные углы для полосы

                        Image{
                            id: image_calendar
                            source: "qrc:/Image/panelInfo/icon_calendar.png" // Путь к изображению стрелки
                            width: 20
                            height: 22
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.margins: 5
                        }

                        Text{
                            id: calendar
                            text:activationDateText
                            color: Style.fontColorValue
                            font.family: Style.fontValue
                            font.pixelSize: Style.fontSizeValue
                            anchors.left: image_calendar.right
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.margins: 5
                        }
                    }
                }

}
