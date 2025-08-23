import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import StyleSetting 1.0

Rectangle {
    id: customTable
    width: parent.width
    height: parent.height
    color: Style.backgroundColor
    //   color: "blue"

    //Таблица типов
    Rectangle {
        id: tableConttrollerType
        //height: 500
        width: 320
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "transparent"
        border.color: Style.borderColor


        // Заголовок таблицы
        Rectangle {
            id: tableConttrollerTypeHeader
            width: parent.width
            height: 43
            //            color: Style.headerColor
            color: "transparent"
            border.color: Style.borderColor
            border.width: 1

            Rectangle {
                id: _left
                width: 320
                height: parent.height
                //                   color: Style.backgroundColor
                color: "transparent"
                border.color: Style.borderColor
                border.width: 1

                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10

                    Item { width: 20; height: 1 } // Отступ

                    Text {
                        width: 70
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Serial ID")
                    }

                    Text {
                        width: 80
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Device")
                    }

                    Text {
                        width: 30
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("FW")
                    }

                    Text {
                        width: 80
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Chanel")
                    }
                }
            }
        }


        //Тело таблицы
        Rectangle {
            id: tableConttrollerTypeData
            width: parent.width
            anchors.left: parent.left
            anchors.top: tableConttrollerTypeHeader.bottom
            anchors.bottom: parent.bottom
            color: "transparent"
            // color: "red"

        }//Тело таблицы
    }

    //Таблиа параметров
    Rectangle {
        id: tableParametors

        anchors.left: tableConttrollerType.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: Style.backgroundColor
        border.color: Style.borderColor

    // Заголовок таблицы
    Rectangle {
        id: tableParametorsHeader
        width: parent.width
        height: 43
        //        color: Style.headerColor
        color: "transparent"
        border.color: Style.borderColor
        border.width: 1


                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10

                    Item { width: 20; height: 1 } // Отступ

                    Text {
                        width: 75
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Group 1")
                    }

                    Text {
                        width: 75
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Group 2")
                    }

                    Text {
                        width: 75
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Group 3")
                    }

                    Text {
                        width: 75
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Group 4")
                    }

                    Text {
                        width: 85
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Description")
                    }

                    Text {
                        width: 75
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Height")
                    }

                    Text {
                        width: 75
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Tilt")
                    }

                    Text {
                        width: 85
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Motor revers")
                    }

                    Text {
                        width: 85
                        height: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: Style.buttonDefaultTextrColor
                        font.pixelSize: Style.fontSizeLabel
                        text: qsTr("Error")
                    }
                }



    }//заголовок
}

}
