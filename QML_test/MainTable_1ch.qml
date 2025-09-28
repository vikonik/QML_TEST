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

    signal rowSelected(int rowIndex)// Сигнал для передачи индекса выбранной строки
    property bool isDragging: false
    property int dragStartRow: -1
    property int dragStartColumn: -1
    property string dragValue: ""
    property var selectedCells: []
    property var currentHoverCell: null

    property var columnWidths: [
        { name: "Serial ID", width: 75 },
        { name: "Devcie", width: 75 },
        { name: "FW", width: 60 },
        { name: "Channel", width: 75 },
        { name: "Error", width: 75 },
        { name: "Group 1", width: 75 },
        { name: "Group 2", width: 75 },
        { name: "Group 3", width: 75 },
        { name: "Group 4", width: 75 },
        { name: "Height", width: 65 },
        { name: "End Angle", width: 70 },
        { name: "Tilt only", width: 65 },
        { name: "Motor revers", width: 90 }
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

    // Функция для определения ячейки по координатам
    function getCellAt(x, y) {
        // Преобразуем координаты в индексы строки и столбца
        var row = Math.floor(y / 30); // Высота строки 30px
        if (row < 0 || row >= rowView.count) return null;

        // Определяем столбец
        var colX = x - 30; // Вычитаем ширину иконки
        if (colX < 0) return null;

        var totalWidth = 0;
        for (var i = 0; i < columnWidths.length; i++) {
            var colWidth = getColumnWidth(columnWidths, i);
            if (colX < totalWidth + colWidth) {
                return {row: row, column: i};
            }
            totalWidth += colWidth;
        }

        return null;
    }

    // Функция для обработки перетаскивания
    function handleDrag(row, column) {
        if (!isDragging) return;

        // Обновляем текущую ячейку под курсором
        currentHoverCell = {row: row, column: column};

        // Определяем диапазон строк и столбцов
        var startRow = Math.min(dragStartRow, row);
        var endRow = Math.max(dragStartRow, row);
        var startCol = Math.min(dragStartColumn, column);
        var endCol = Math.max(dragStartColumn, column);

        // Заполняем массив выбранных ячеек
        selectedCells = [];
        for (var r = startRow; r <= endRow; r++) {
            for (var c = startCol; c <= endCol; c++) {
                if (c >= 5 && c <= 8) { // Только столбцы 5-8 (Group 1-4)
                    selectedCells.push({row: r, column: c});

                    // Обновляем значение ячейки
                    if (tableModel) {
                        tableModel.updateCell(r, c, dragValue);
                    }
                }
            }
        }
    }

    // Функция для завершения перетаскивания
    function endDrag() {
        isDragging = false;
        selectedCells = [];
        currentHoverCell = null;
    }

    ListView {
        id: rowView
        anchors.fill: parent
        model: tableModel
        spacing: 0
        interactive: false
        property int selectedRow: -1

        // Главный MouseArea для перетаскивания - теперь внутри ListView
        MouseArea {
            id: dragMouseArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton
            propagateComposedEvents: true

            onPressed: {
                var cell = getCellAt(mouseX, mouseY);
                if (cell && mouse.modifiers & Qt.ControlModifier && cell.column >= 5 && cell.column <= 8) {
                    // Начинаем перетаскивание
                    content.isDragging = true;
                    content.dragStartRow = cell.row;
                    content.dragStartColumn = cell.column;

                    // Получаем значение из модели
                    var modelIndex = tableModel.index(cell.row, 0);
                    var rowData = tableModel.data(modelIndex, TableModel.RowDataRole);
                    if (rowData && rowData.length > cell.column) {
                        content.dragValue = rowData[cell.column];
                    }

                    // Обрабатываем начальную ячейку
                    handleDrag(cell.row, cell.column);

                    // Перехватываем событие
                    mouse.accepted = true;
                } else {
                    // Пропускаем событие дальше
                    mouse.accepted = false;
                }
            }

            onPositionChanged: {
                if (isDragging) {
                    var cell = getCellAt(mouseX, mouseY);
                    if (cell) {
                        handleDrag(cell.row, cell.column);
                    }
                    mouse.accepted = true;
                } else {
                    mouse.accepted = false;
                }
            }

            onReleased: {
                if (isDragging) {
                    endDrag();
                    mouse.accepted = true;
                } else {
                    mouse.accepted = false;
                }
            }
        }

        delegate: Rectangle {
            id: rowDelegate
            width: rowView.width
            height: 30

            property int rowIndex: index
            property bool isSelected: rowView.selectedRow === rowIndex

            color: isSelected ? Style.selectedRowColor : (rowIndex % 2 === 0 ? Style.rowEvenColor : Style.rowOddColor)

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
                    onClicked: {
                        rowView.selectedRow = rowIndex;
                        content.rowSelected(rowIndex);
                        tableController.processRow(rowIndex);
                    }
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
                        width: getColumnWidth(columnWidths, model.index)
                        height: parent.height
                        color: "transparent"

                        // Добавляем правую границу для ячейки с индексом 4
                        Rectangle {
                            anchors.right: parent.right
                            width: 1
                            height: parent.height
                            color: columnIndex === 4 ? Style.borderColor : "transparent"
                            visible: columnIndex === 4
                            border.width: 2
                        }

                        property int columnIndex: model.index
                        property int actualRowIndex: rowDelegate.rowIndex
                        property string columnName: content.getColumnName(content.columnWidths, columnIndex)
                        property bool editable: columnName === "Group 1" || columnName === "Group 2" ||
                                                columnName === "Group 3" || columnName === "Group 4" ||
                                                columnName === "Height"|| columnName === "End Angle"

                        // Визуальное выделение при перетаскивании
                        Rectangle {
                            anchors.fill: parent
                            color: {
                                if (!content.isDragging) return "transparent";

                                // Проверяем, находится ли ячейка в выбранном диапазоне
                                for (var i = 0; i < content.selectedCells.length; i++) {
                                    var cell = content.selectedCells[i];
                                    if (cell.row === actualRowIndex && cell.column === columnIndex) {
                                        return Qt.rgba(0, 1, 0, 0.3); // Зеленый с прозрачностью
                                    }
                                }

                                return "transparent";
                            }
                        }

                        // Область для выбора строки
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton
                            propagateComposedEvents: true

                            onClicked: {
                                rowView.selectedRow = rowIndex;
                                tableController.processRow(rowIndex);
                                mouse.accepted = false; // Пропускаем событие дальше
                            }

                            onDoubleClicked: {
                                console.log("Double Click")
                                if (cellDelegate.editable && !textInput.visible) {
                                    startEditing()
                                }
                                mouse.accepted = false; // Пропускаем событие дальше
                            }
                        }

                        Rectangle {//Для отрисовки границ
                            width: getColumnWidth(columnWidths, index)
                            height: parent.height
                            border.width: 1
                            color: "transparent"

                            Row {
                                id: imageTextRow
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                    leftMargin: 10
                                    right: parent.right
                                }
                                visible:  (columnName === "Group 1" || columnName === "Group 2" ||
                                           columnName === "Group 3" || columnName === "Group 4" ||
                                           columnName === "End Angle" || columnName === "Error") && !textInput.visible

                                //изображение и текст
                                Image {
                                    id: cellIcon
                                    height: 16
                                    source: {
                                        if(columnName === "End Angle")
                                            return "qrc:/Image/iconTilt.png";
                                        else if( columnName === "Error" && modelData !== "00")
                                            return "qrc:/Image/iconError.png";
                                        else if(columnName === "Group 1" || columnName === "Group 2" || columnName === "Group 3" || columnName === "Group 4")
                                            return "qrc:/Image/iconGroup.png";
                                        else
                                            return "";
                                    }
                                    anchors.verticalCenter: parent.verticalCenter
                                    visible: source !== ""
                                }

                                Text {
                                    text: (columnName === "Error" && modelData === "00") ? "" : modelData
                                    elide: Text.ElideMiddle
                                    color: Style.buttonDefaultTextrColor
                                    font.pixelSize: Style.fontSizeLabel
                                    horizontalAlignment: columnName === "Serial ID" ? Text.AlignLeft : Text.AlignHCenter
                                }
                            }
                        }

                        //Специальный Checkbox для таблицы
                        CustomCheckBoxTable {
                            id: customCheckBoxTable
                            anchors.centerIn: parent
                            visible:  (columnName === "Tilt only" ||  columnName === "Motor revers" )&& !textInput.visible
                            checked: modelData === "1" || modelData === "true"
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
                                      columnName !== "Group 3" && columnName !== "Group 4" &&
                                      columnName !== "End Angle" && columnName !== "End Angle" && columnName !== "Motor revers" &&
                                      columnName !== "Tilt only"  &&  columnName !== "Error")
                            horizontalAlignment: columnName === "Serial ID" ? Text.AlignLeft : Text.AlignHCenter
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
                            visible: cellDelegate.editable && activeFocus
                            text: modelData
                            font.pixelSize: 12
                            clip: true
                            selectByMouse: true

                            onEditingFinished: finishEditing()
                            onActiveFocusChanged: if (!activeFocus) finishEditing()
                            horizontalAlignment: Text.AlignHCenter
                        }

                        function startEditing() {
                            textInput.text = modelData
                            textInput.visible = true
                            textInput.forceActiveFocus()
                            textInput.selectAll()
                        }

                        function finishEditing() {
                            if (textInput.visible) {
                                tableModel.updateCell(actualRowIndex, columnIndex, textInput.text)
                                textInput.visible = false
                            }
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
