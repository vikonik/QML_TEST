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
        { name: "Devcie", width: 75 },
        { name: "FW", width: 60 },
        { name: "Channel", width: 75 },
        { name: "Error", width: 75 }
    ]

    property var columnsDataDef: [
        { name: "Group 1", width: 75 },
        { name: "Group 2", width: 75 },
        { name: "Group 3", width: 75 },
        { name: "Group 4", width: 75 },
        { name: "Height", width: 65 },
        { name: "End Angle", width: 70 },
        { name: "Tilt only", width: 65 },
        { name: "Motor revers", width: 90 }

    ]

    signal rowSelected(int rowIndex)// Сигнал для передачи данных строки

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

    readonly property int columntableConttrollerWidth: getColumnWidth(columnsHeaderDef, 0) +
                                        getColumnWidth(columnsHeaderDef, 1) +
                                        getColumnWidth(columnsHeaderDef, 2) +
                                        getColumnWidth(columnsHeaderDef, 3) +
                                        getColumnWidth(columnsHeaderDef, 4)

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
            //border.color: "red"
            border.width: 1

            Rectangle {
                id: _left
               width:  columntableConttrollerWidth + 30
//               Component.onCompleted: {
//                   console.log("Ширина заголовка:",columntableConttrollerWidth)
//                   console.log("Ширина заголовка:",width)
//                }
                height: parent.height
                //                   color: Style.backgroundColor
                color: "transparent"
                //color: "green"
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
                // Обрабатываем сигнал из внутренней таблицы
                onRowSelected: {
                    // Пробрасываем сигнал наружу
                    customTable.rowSelected(rowIndex)
                }
            }

        }//Тело таблицы
    }


}


