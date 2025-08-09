import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
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

    Rectangle {
           id: tableBody
           width: parent.width
           color: Style.backgroundColor
           border.color: Style.borderColor
           border.width: 1
           anchors.top: customTableHeader.bottom
           anchors.bottom: parent.bottom

           TableView {
               id: tableView
               anchors.fill: parent
               columnSpacing: 1
               rowSpacing: 1
               clip: true
               model: tableModel

               delegate: Rectangle {
                   id: cellDelegate
                   color: "blue"
                   /*row === tableModel.selectedRow ? Style.selectedColor :
                          (row % 2 === 0 ? Style.rowEvenColor : Style.rowOddColor)*/
                   border.width: 1
                   border.color: Style.borderColor

                   // Первый столбец - выбор строки
                   Loader {
                       anchors.fill: parent
                       sourceComponent: {

                           if (tableModel.isColumnEditable(column)) {
                               return editableComponent
                           } else {
                               return readOnlyComponent
                           }
                       }

                       property var cellValue: display
                   }
               }
           }
       }

       // Компоненты ячеек
       Component {
           id: selectorComponent
           Rectangle {
               color: "transparent"
               MouseArea {
                   anchors.fill: parent
                   onClicked: tableModel.selectRow(row)
               }
               Text {
                   text: "✓"
                   //visible: row === tableModel.selectedRow
                   anchors.centerIn: parent
                   font.bold: true
                   color: Style.fontColorValue
               }
           }
       }

       Component {
           id: readOnlyComponent
           Text {
               text: cellValue
               padding: 10
               color: Style.fontColorValue
               elide: Text.ElideRight
               verticalAlignment: Text.AlignVCenter
               anchors.fill: parent
           }
       }

       Component {
           id: editableComponent
           TextField {
               text: cellValue
               padding: 5
               color: Style.fontColorValue
               background: Rectangle {
                   color: "transparent"
                   border.width: 1
                   border.color: Style.borderColor
               }
               onEditingFinished: {
                   var idx = tableModel.index(row, column);
                   tableModel.setData(idx, text);
               }
           }
       }

/*
    Rectangle{//Таблица
        id:tableBody
        width: parent.width
//        height: 100//parent.height - customTableHeader
        color: Style.backgroundColor
        //color: "yellow"
        border.color: Style.borderColor
        border.width: 1
        anchors.top: customTableHeader.bottom
        anchors.bottom: parent.bottom
//        anchors.left: _left.right
        anchors.right: parent.right
    ScrollView {
            anchors.fill: parent
            clip: true

            ListView {
                id: listView
                model: tableModel
                boundsBehavior: Flickable.StopAtBounds
                spacing: 1
                cacheBuffer: 1000 // Для плавной прокрутки

                delegate: RowLayout {
                    id: rowDelegate
                    width: listView.width
                    spacing: 1
                    property bool isSelected: model.row === tableModel.selectedRow

                    // Выделение всей строки
                    Rectangle {
                        width: listView.width
                        height: 30
                        color: isSelected ? "#e0f0ff" : (index % 2 === 0 ? "#f0f0f0" : "#ffffff")
                        border.color: "#cccccc"
                        border.width: 1

                        Row {
                            anchors.fill: parent
                            spacing: 1

                            // Колонка 0 - выбор строки
                            Rectangle {
                                width: 50
                                height: parent.height
                                color: "transparent"

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: tableModel.selectRow(model.row)
                                }

                                Text {
                                    text: "✓"
                                    visible: isSelected
                                    anchors.centerIn: parent
                                    font.bold: true
                                }
                            }

                            // Колонки 1-14
                            Repeater {
                                model: 14 // Остальные 14 столбцов

                                Loader {
                                    width: (listView.width - 50) / 14
                                    height: parent.height

                                    sourceComponent: {
                                        // Редактируемые колонки (3-7)
                                        if (index >= 2 && index <= 6) {
                                            return editableComponent;
                                        } else {
                                            return readOnlyComponent;
                                        }
                                    }

                                    property int columnIndex: index + 1
                                    property string cellValue: model.display ? model.display[row][columnIndex] : ""
                                }
                            }
                        }
                    }
                }
            }
        }

        // Компоненты для ячеек
        Component {
            id: readOnlyComponent

            Rectangle {
                color: "transparent"

                Text {
                    anchors.fill: parent
                    anchors.margins: 5
                    text: cellValue
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
            }
        }

        Component {
            id: editableComponent

            Rectangle {
                color: "transparent"

                TextField {
                    anchors.fill: parent
                    anchors.margins: 1
                    text: cellValue
                    background: Rectangle { color: "blue" }

                    onEditingFinished: {
                        tableModel.setData(
                            tableModel.index(model.row, columnIndex),
                            text
                        );
                    }
                }
            }
        }

 }//Таблица*/
}
