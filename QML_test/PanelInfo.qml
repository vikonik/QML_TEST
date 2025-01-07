import QtQuick 2.0
import StyleSetting 1.0


Item {
    id: panelInfo
    width: 223
    height: 134
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

            Text{
                id: serial
                text:"90"
                color: Style.fontColorValue
                font.family: Style.fontValue
                font.pixelSize: Style.fontSizeValue
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 35
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
                    text:"2089"
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
                        text:"1-Ch"
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
                            text:"08.12.04"
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
