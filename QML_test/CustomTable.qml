import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Rectangle {
    width: 100
    height: 50
    color: "red"  // заливка красным цветом
//    ScrollView {
//            anchors.fill: parent
//            clip: true

//            ListView {
//                id: listView
//                model: tableModel
//                boundsBehavior: Flickable.StopAtBounds
//                spacing: 1
//                cacheBuffer: 1000 // Для плавной прокрутки

//                delegate: RowLayout {
//                    id: rowDelegate
//                    width: listView.width
//                    spacing: 1
//                    property bool isSelected: model.row === tableModel.selectedRow

//                    // Выделение всей строки
//                    Rectangle {
//                        width: listView.width
//                        height: 30
//                        color: isSelected ? "#e0f0ff" : (index % 2 === 0 ? "#f0f0f0" : "#ffffff")
//                        border.color: "#cccccc"
//                        border.width: 1

//                        Row {
//                            anchors.fill: parent
//                            spacing: 1

//                            // Колонка 0 - выбор строки
//                            Rectangle {
//                                width: 50
//                                height: parent.height
//                                color: "transparent"

//                                MouseArea {
//                                    anchors.fill: parent
//                                    onClicked: tableModel.selectRow(model.row)
//                                }

//                                Text {
//                                    text: "✓"
//                                    visible: isSelected
//                                    anchors.centerIn: parent
//                                    font.bold: true
//                                }
//                            }

//                            // Колонки 1-14
//                            Repeater {
//                                model: 14 // Остальные 14 столбцов

//                                Loader {
//                                    width: (listView.width - 50) / 14
//                                    height: parent.height

//                                    sourceComponent: {
//                                        // Редактируемые колонки (3-7)
//                                        if (index >= 2 && index <= 6) {
//                                            return editableComponent;
//                                        } else {
//                                            return readOnlyComponent;
//                                        }
//                                    }

//                                    property int columnIndex: index + 1
//                                    property string cellValue: model.display ? model.display[row][columnIndex] : ""
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        // Компоненты для ячеек
//        Component {
//            id: readOnlyComponent

//            Rectangle {
//                color: "transparent"

//                Text {
//                    anchors.fill: parent
//                    anchors.margins: 5
//                    text: cellValue
//                    verticalAlignment: Text.AlignVCenter
//                    elide: Text.ElideRight
//                }
//            }
//        }

//        Component {
//            id: editableComponent

//            Rectangle {
//                color: "transparent"

//                TextField {
//                    anchors.fill: parent
//                    anchors.margins: 1
//                    text: cellValue
//                    background: Rectangle { color: "white" }

//                    onEditingFinished: {
//                        tableModel.setData(
//                            tableModel.index(model.row, columnIndex),
//                            text
//                        );
//                    }
//                }
//            }
//        }
}
