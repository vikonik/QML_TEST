/*
Это табдица отображает строку состояния кажого устройства
*/
import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import StyleSetting 1.0

Rectangle {
    id: content
    anchors.fill: parent
    color: "transparent"
    // Массив ширины колонок (пример значений)
    //   property var columnWidths: [75, 75, 50, 80]

    property var columnWidths: [
        { name: "Serial ID", width: 75 },
        { name: "Name", width: 75 },
        { name: "Type", width: 60 },
        { name: "Status", width: 80 },
        { name: "Group 1", width: 80 },
        { name: "Group 2", width: 75 },
        { name: "Group 3", width: 75 },
        { name: "Group 4", width: 75 },
        { name: "Height", width: 65 },
        { name: "Tilt", width: 50 },
        { name: "Tilt only", width: 60 },
        { name: "Motor revers", width: 85 },
        { name: "Error", width: 70 }
    ]

    function getColumnWidth(columnsArray, columnIndex) {
        if (columnIndex >= 0 && columnIndex < columnsArray.length) {
            return columnsArray[columnIndex].width;
        }
        return 100; // значение по умолчанию
    }

    function getColumnName(columnsArray, columnIndex) {
        if (columnIndex >= 0 && columnIndex < columnsArray.length) {
            return columnsArray[columnIndex].name;
        }
        return "";
    }


    ListView {
        id: rowView
        anchors.fill: parent
        model: tableModel
        spacing: 0

        property int selectedRow: -1

        delegate: Rectangle {
            id: rowDelegate
            width: rowView.width
            height: 30

            property int rowIndex: index
            property bool isSelected: rowView.selectedRow === rowIndex

            color: isSelected ? Style.selectedRowColor : (rowIndex % 2 === 0 ? Style.rowEvenColor : Style.rowOddColor)
            //color: isSelected ? "red" : "green"
            // Иконка в начале строки
            Rectangle {
                width: 30
                height: parent.height
                color: "transparent"

                Image {
                    width: 20
                    height: 20
                    anchors.centerIn: parent
                    source: rowDelegate.isSelected ? "qrc:/Image/panelInfo/icon_cube_yellow.png"
                                                   : "qrc:/Image/iconSerialID.png"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: rowView.selectedRow = rowIndex
                }
            }

            // Ячейки таблицы
            Row {
                anchors {
                    left: parent.left
                    leftMargin: 30
                }
                height: parent.height
                spacing: 0

                Repeater {
                    model: rowData

                    delegate: Rectangle {
                        id: cellDelegate
                        // Используем ширину из массива, если он определен и имеет достаточную длину
                        //                        width: (content.columnWidths && content.columnWidths.length > model.index) ?
                        //                               content.columnWidths[model.index] : 75
                        width: getColumnWidth(columnWidths, model.index)

                        height: parent.height
                        color: "transparent"
                        //color: "blue"
                        //border.color: "blue"
                        //border.width: 1

                        // Добавляем правую границу для ячейки с индексом 3
                        Rectangle {
                            anchors.right: parent.right
                            width: 1
                            height: parent.height
                            color: columnIndex === 3 ? Style.borderColor : "transparent"
                            visible: columnIndex === 3
                            border.width: 2
                        }

                        property int columnIndex: model.index
                        property int actualRowIndex: rowDelegate.rowIndex
                        property string columnName: content.getColumnName(content.columnWidths, columnIndex)

                        // Область для выбора строки
                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            onClicked: {
                                rowView.selectedRow = rowIndex
                            }
                        }

                        Rectangle{//Для отрисовки границ
                            width: getColumnWidth(columnWidths, index)
                            height: parent.height
                            border.color: "transparent"
                            // border.color: columnIndex === 3 ? Style.specialBorderColor : "transparent"
                            border.width: 1
                            color: "transparent"
                            //color: columnIndex === 3 ? Style.specialBorderColor : Style.defaultBorderColor

                            Row {
                                id: imageTextRow
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                    leftMargin: 10
                                    right: parent.right
                                }
                                //   spacing: 10
                                visible:  (columnName === "Group 1" || columnName === "Group 2" ||
                                           columnName === "Group 3" || columnName === "Group 4" ||
                                           columnName === "Tilt" || columnName === "Error") && !textInput.visible

                                //изображение и текст
                                Image {
                                    id: cellIcon
                                    // width: 16
                                    height: 16
                                    source: {
                                        if(columnName === "Tilt")
                                            return "qrc:/Image/iconTilt.png";
                                        else if( columnName === "Error" && rowData !== "00")
                                            return "qrc:/Image/iconError.png";

                                        else
                                            return "qrc:/Image/iconGroup.png";
                                    }
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Text {
                                    text: modelData
                                    elide: Text.ElideMiddle
                                    color: Style.buttonDefaultTextrColor
                                    font.pixelSize: Style.fontSizeLabel
                                    horizontalAlignment: columnIndex === 0 ? Text.AlignLeft : Text.AlignHCenter
                                }
                            }
                        }

                            //Специальный Checkbox для таблицы
                            CustomCheckBoxTable {
                                id: customCheckBoxTable
                                anchors.centerIn: parent
                                visible:  (columnName === "Tilt only" ||  columnName === "Motor revers" )&& !textInput.visible
                                checked: rowData === "1" || rowData === "true" // Поддержка разных форматов
                                color: "transparent"
                                onToggled: {
                                    tableModel.updateCell(actualRowIndex, columnIndex, checked ? "1" : "0")
                                }
                            }


                        // Обычный текст для других колонок
                        Text {
                            id: textDisplay
                            anchors {
                                verticalCenter: parent.verticalCenter
                                left: parent.left
                                leftMargin: 10
                                right: parent.right
                            }
                            text: modelData
                            elide: Text.ElideMiddle
                            color: Style.buttonDefaultTextrColor
                            font.pixelSize: Style.fontSizeLabel
                            visible: (columnName !== "Group 1" && columnName !== "Group 2" &&
                                      columnName !== "Group 3"&& columnName !== "Group 4" &&
                                      columnName !== "Tilt only" && columnName !== "Motor revers" &&
                                      columnName !== "Tilt"  && columnName !== "Error")
                            horizontalAlignment: columnIndex === 0 ? Text.AlignLeft : Text.AlignHCenter
                        }


                        // Поле ввода
                        TextInput {
                            id: textInput
                            anchors {
                                verticalCenter: parent.verticalCenter
                                left: parent.left
                                leftMargin: 10
                                right: parent.right
                            }
                            text: modelData
                            font.pixelSize: 12
                            visible: false
                            clip: true
                            selectByMouse: true

                            onEditingFinished: finishEditing()
                            onActiveFocusChanged: if (!activeFocus) finishEditing()
                        }
                    }
                }
            }

            // Нижняя граница для строки
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: "#2B2B2B"
            }
        }
    }
}
