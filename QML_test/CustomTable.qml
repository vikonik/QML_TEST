import QtQuick 2.0
import StyleSetting 1.0


Rectangle {
id:customTable
width: parent.width
height: parent.height
color: "green"
Rectangle{//Заголовок
id:customTableHeader
width: parent.width
height: 43
color: "red"

//color: Style.backgroundColor
border.color: Style.borderColor
border.width: 1
Row{
    height: parent.height//Этого поля в Row нет, но добавим его для работы с Rectangle
    width: parent.width
    spacing: 30
    anchors.verticalCenter: parent.verticalCenter
Rectangle{
    id:_left
    width: 371
    height: parent.height
  //  color: "blue"
   color: Style.backgroundColor
    border.color: Style.borderColor
    border.width: 1
    Row{
//        spacing: 30
        anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            width: 20 // Отступ от левого края
            height: 1 // Высота минимальная, чтобы не занимать лишнего пространства
            color: "transparent" // Прозрачный фон
        }

        Text {
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Serial ID")
        }
        Text {
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Device")
        }
        Text {
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("FW")
        }
        Text {
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Chanel")
        }
    }
}

Rectangle{
    id:_rigcht
  //  width: 100
    height: parent.height
    color: Style.backgroundColor
   // color: "yellow"
    border.color: Style.borderColor
    border.width: 1
    anchors.left: _left.right
    anchors.right: parent.right
    Row{

        anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            width: 20 // Отступ от левого края
            height: 1 // Высота минимальная, чтобы не занимать лишнего пространства
            color: "transparent" // Прозрачный фон
        }

        Text {
            id: group_1
            width: 75
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Group 1")
        }
        Text {
            id: group_2
            width: 75
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Group 2")
        }
        Text {
            id: group_3
            width: 75
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Group 3")
        }
        Text {
            id: group_4
            width: 75
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Group 4")
        }
        Text {
    //        id: name
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Description")
        }
        Text {
    //        id: name
            width: 75
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Height")
        }
        Text {
    //        id: name
            width: 75
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Tilt")
        }
        Text {
    //        id: name
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Motor revers")
        }
        Text {
    //        id: name
            width: 85
            height: 30 // Установите высоту, чтобы можно было выровнять текст вертикально
            horizontalAlignment: Text.AlignHCenter // Горизонтальное выравнивание по центру
            verticalAlignment: Text.AlignVCenter // Вертикальное выравнивание по центру
            color: Style.buttonDefaultTextrColor
            font.pixelSize: Style.fontSizeLabel
            text: qsTr("Error")
        }
    }
}

}

}//Заголовок

Rectangle{//Таблица

}//Таблица
}//Основное поле


