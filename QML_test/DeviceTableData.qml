import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import StyleSetting 1.0

Rectangle {
    id: content
    anchors.fill: parent

    // Массив ширины колонок (пример значений)
    property var columnWidths: [95, 75, 30, 90]

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

            color: isSelected ? "#c0d8f0" : (rowIndex % 2 === 0 ? "#f0f0f0" : "#ffffff")

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
                        width: (content.columnWidths && content.columnWidths.length > model.index) ?
                               content.columnWidths[model.index] : 75
                        height: parent.height
                        color: "transparent"

                        property int columnIndex: model.index
                        property int actualRowIndex: rowDelegate.rowIndex

                        // Область для выбора строки
                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            onClicked: {
                                rowView.selectedRow = rowIndex
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
                            visible: (columnIndex !== 4 && columnIndex !== 5)
                        }
                    }
                }
            }

            // Нижняя граница для строки
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: "#e0e0e0"
            }
        }
    }
}
