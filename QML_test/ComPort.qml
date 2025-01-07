import QtQuick 2.4
import QtQuick.Controls 2.15
import StyleSetting 1.0

Item {
    Text{
        id: labelComPort
        text: "Com Port"
        color: Style.fontColorLabel
        font.family: Style.fontLabel
        font.pixelSize: Style.fontSizeLabel
        x: 17
    }


    Row{
        anchors.top: labelComPort.bottom
        anchors.topMargin: 5 // Отступ сверху
        x: labelComPort.x
        //anchors.centerIn: parent
        spacing: 10  // Расстояние между элементами

        Rectangle{
            //x:150
            width: 123
            height: 42
            color: Style.backgroundColor

            ComboBox {
                id: comboBox
                width: 123//parent.width
                height: 42//parent.height
                //            anchors.top: labelComPort.bottom
                //            anchors.topMargin: 5 // Отступ сверху
                //            x: labelComPort.x

                model: ["Option 1", "Option 2", "Option 3"] // Данные для ComboBox
                font.family: Style.fontValue // Тип шрифта
                font.pixelSize: Style.fontSizeValue // Размер шрифта


                //            // Цвет текста текущего выбранного элемента
                //            textRole: "color"
                //            currentIndex: 0 // Выбор первого элемента по умолчанию

                background: Rectangle {
                    // Внешний вид ComboBox
                    width: comboBox.width
                    height: comboBox.height
                    color: Style.backgroundColor // Цвет фона
                    radius: 5 // Скругленные углы
                    border.color: Style.borderColor // Цвет границы
                    border.width: 2


                    //                Row {
                    //                    anchors.fill: parent
                    //                    spacing: 5


                    //                    Text {

                    //                        anchors.verticalCenter: parent.verticalCenter
                    //                        anchors.left: parent.left
                    //                        anchors.margins: 5
                    //                        text: comboBox.currentText // Отображаемый текст
                    //                        color: "#FF0000" // Цвет текста
                    //                        font.family: Style.fontValue
                    //                        font.pixelSize: Style.fontSizeValue
                    //                        elide: Text.ElideRight
                    //                    }


                    Image {
                        source: "qrc:/Image/ComboBoxArrow.png" // Путь к изображению стрелки
                        width: 12
                        height: 7
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 10
                    }
                    //                }
                }


                indicator: Item {
                    // Полностью скрываем стандартный индикатор
                    width: 0
                    height: 0
                }

                //            popup: Popup {
                //                id: comboPopup
                //                width: comboBox.width
                //                y: comboBox.height // Позиция выпадающего списка
                //                modal: true

                //                ListView {
                //                    width: parent.width
                //                    height: contentHeight
                //                    model: comboBox.delegateModel

                //                    delegate: Item {
                //                        width: comboPopup.width
                //                        height: 40

                //                        Rectangle {
                //                            width: parent.width
                //                            height: parent.height
                //                            color: ListView.isCurrentItem ? "#505050" : "#333333" // Выделение текущего элемента
                //                            radius: 8 // Скругленные углы для элементов списка

                //                            Text {
                //                                anchors.centerIn: parent
                //                                text: modelData
                //                                color: "#FFFFFF"
                //                                font.family: "Roboto"
                //                                font.pixelSize: 14
                //                            }

                //                            MouseArea {
                //                                anchors.fill: parent
                //                                onClicked: {
                //                                    comboBox.currentIndex = index // Устанавливаем выбранный элемент
                //                                    comboBox.close() // Закрываем выпадающий список
                //                                }
                //                            }
                //                        }
                //                    }
                //                }
                //            }
            }
            //    }

            //По другому скрыть текст фона не получилось
            Rectangle {
                width: 123-2
                height: 42-2
                //color: Style.backgroundColor
                color:"transparent"
                anchors.top: labelComPort.bottom
                anchors.topMargin: 5+1 // Отступ сверху
                x: labelComPort.x+1
                radius: 5

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.margins: 10
                    text: comboBox.currentText // Отображаемый текст
                    color: Style.fontColorValue // Цвет текста
                    font.family: Style.fontValue
                    font.pixelSize: Style.fontSizeValue
                    elide: Text.ElideRight
                }
            }
        }

        CustomButton {
            id: rectButtonConnect
            x:150
            width: 42
            height: 42
            color: "transparent"

            defaultImage: "qrc:/Image/ComPortConnect_idl.png"
            hoverImage: "qrc:/Image/ComPortConnect_select.png"
            pressedImage: "qrc:/Image/ComPortConnect_Preset.png"

            onClicked: console.log("Disconnect button clicked")
        }

        CustomButton {
            id: rectButtonDisconnect
            x: 150
            width: 42
            height: 42
            color: "transparent"

            defaultImage: "qrc:/Image/ComPortDisconnect_idl.png"
            hoverImage: "qrc:/Image/ComPortDsconnect_select.png"
            pressedImage: "qrc:/Image/ComPortDisconnect_Preset.png"

            onClicked: console.log("Disconnect button clicked")
        }

    }//Row


    //Поля
    //Кнопки Read и Programm
}
