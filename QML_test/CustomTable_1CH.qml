import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import StyleSetting 1.0

Rectangle {
    id: customTable
    width: parent.width
    height: parent.height
    color: Style.backgroundColor
    //color: "blue"

    // Массив ширины колонок (пример значений)
    //  property var columnWidths: [75, 75, 50, 80]
    property var columnsHeaderDef: [
        { name: "Serial ID", width: 75 },
        { name: "Name", width: 75 },
        { name: "Type", width: 60 },
        { name: "Status", width: 75 }
    ]

    property var columnsDataDef: [
        { name: "Group 1", width: 75 },
        { name: "Group 2", width: 75 },
        { name: "Group 3", width: 75 },
        { name: "Group 4", width: 75 },
        { name: "Height", width: 65 },
        { name: "Tilt", width: 50 },
        { name: "Tilt only", width: 60 },
        { name: "Motor revers", width: 85 },
        { name: "Error", width: 70 }

    ]


    readonly property int columnSerialId: 0
    readonly property int columnName: 1
    readonly property int columnType: 2
    readonly property int columnStatus: 3

    function getColumnName(columnsArray, columnIndex) {
        if (columnIndex >= 0 && columnIndex < columnsArray.length) {
            return columnsArray[columnIndex].name;
        }
        return "";
    }

    function getColumnWidth(columnsArray, columnIndex) {
        if (columnIndex >= 0 && columnIndex < columnsArray.length) {
            return columnsArray[columnIndex].width;
        }
        return 100; // значение по умолчанию
    }

    //Таблица типов
    Rectangle {
        id: tableConttrollerType
        //height: 500
        width: parent.width
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
            //color: "green"
            border.color: Style.borderColor
            border.width: 1

            Rectangle {
                id: _left
                width: 320
                height: parent.height
                //                   color: Style.backgroundColor
                color: "transparent"
                //                color: "green"
                border.color: Style.borderColor
                border.width: 1


                Row {
                    anchors.verticalCenter: parent.verticalCenter
                   // spacing: 10

                    Item { width: 30; height: 1 } // Отступ

                    Repeater {
                        model: columnsHeaderDef.length
                        Rectangle{
                            width: getColumnWidth(columnsHeaderDef, index)
                            height: _left.height
                            border.color: "transparent"
                            border.width: 1
                            color: "transparent"
                            Text {
                                anchors.centerIn: parent  // Центрирование текста относительно родителя
//                                width: getColumnWidth(columnsHeaderDef, index)
//                                height: 30
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                color: Style.buttonDefaultTextrColor
                                font.pixelSize: Style.fontSizeLabel
                                text: getColumnName(columnsHeaderDef, index)

                            }
                        }
                    }
                }
            }

            // Заголовок таблицы
            Rectangle {
                id: tableParametorsHeader
                //width: parent.width
                height: 43
                anchors.left: _left.right
                anchors.right: parent.right
                //        color: Style.headerColor
                color: "transparent"
                border.color: Style.borderColor
                border.width: 1


                Row {
                    anchors.verticalCenter: parent.verticalCenter
 //                   spacing: 10

//                    Item { width: 1; height: 1 } // Отступ

                    Repeater {
                        model: columnsDataDef.length
                        Rectangle{
                            width: getColumnWidth(columnsDataDef, index)
                            height: tableParametorsHeader.height
                            border.color: "transparent"
                            border.width: 1
                            color: "transparent"
                            Text {
//                                width: getColumnWidth(columnsDataDef, index)
//                                height: 30
                                anchors.centerIn: parent  // Центрирование текста относительно родителя
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                color: Style.buttonDefaultTextrColor
                                font.pixelSize: Style.fontSizeLabel
                                text: getColumnName(columnsDataDef, index)

                            }
                        }
                    }
                }
            }//заголовок


        }


        //Тело таблицы
        Rectangle {
            id: tableConttrollerTypeData
            width: parent.width
            anchors.left: parent.left
            anchors.top: tableConttrollerTypeHeader.bottom
            anchors.bottom: parent.bottom
              color: "transparent"
            //color: "red"
            //            DeviceTable{

            //            }
            MainTable_1ch{

            }

        }//Тело таблицы
    }


}


