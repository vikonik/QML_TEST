import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import StyleSetting 1.0

ApplicationWindow {
    id: mainWindow  // Уникальный идентификатор окна
    visible: true
    width: 1280
    height: 900
    title: "Configuration Tool 2024"

    flags: Qt.FramelessWindowHint //| Qt.WindowTransparentForInput  // Убираем стандартный заголовок
    color: "transparent"//Делаем углы прозрачными

    // Переменные для отслеживания положения мыши и окна
    property real dragStartX: 0
    property real dragStartY: 0
    property real initialWindowX: 0
    property real initialWindowY: 0


    // Фон для визуализации окна
    Rectangle {
        anchors.fill: parent
        color: Style.backgroundColor
        radius: 10       // Радиус скругления углов

        // Заголовок окна для перетаскивания
        Rectangle {
            id: titleBar
            width: parent.width
            height: 47
            color: Style.backgroundColor
            radius: parent.radius

            //Пиктограмма в верхнем левом углу
            Rectangle{
                width: 17
                height: 12
                x: 17
                y: 16
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/Image/LeftPicto.png"
                }
            }

            // Кнопка для управления отображением панели
            Button {
                id: toggleButton
                z: 2
                width: 21  // Устанавливаем фиксированную ширину
                height: 21  // Устанавливаем фиксированную высоту

                //text: sidePanel.visible ? "Скрыть панель" : "Показать панель"
                anchors.verticalCenter: parent.verticalCenter // Центрирование по вертикали
                anchors.left: parent.left // Привязка к левому краю родительского элемента
                anchors.leftMargin: 247 // Отступ от левого края

                background: Rectangle {
                    color: Style.backgroundColor
                }

                // Используем изображение как содержимое кнопки
                contentItem: Image {
                    source: "qrc:/Image/Group 41.png"  // Путь к картинке через ресурсный файл
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit

                    onStatusChanged: {
                        if (status === Image.Error) {
                            console.log("Ошибка загрузки изображения: ", source);
                        }
                    }
                }

                onClicked: {
                    sidePanel.visible = !sidePanel.visible
                    toggleButton.text = sidePanel.visible ? "Скрыть панель" : "Показать панель"
                    //                    if(!!sidePanel.visible){
                    //                        workPanel.width = mainWindow.width - statusBar.width
                    //                    }
                    //                    else{
                    //                        workPanel.width = mainWindow.width
                    //                    }
                }
            }
            Rectangle{
                width: 24
                height: 24
                //    x: 17
                //    y: 16
                anchors.right:  appLabel.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 10
                color: "transparent"
                Image {
                    anchors.fill: parent
                    source: "qrc:/Image/ConfigToolPicto.png"
                }
            }
            Text {//Название приложения
                id: appLabel
                text: "Configuration Tool 2024"
                anchors.centerIn: parent
                font.family: "Roboto-Medium" // Название шрифта
                font.pixelSize: 16
                color: "white"
            }

            /**** Алгоритм перетскиваиня окна ****/
            MouseArea {
                id: dragArea
                anchors.fill: parent

                onPressed: {
                    dragStartX = mouse.x
                    dragStartY =  mouse.y
                    initialWindowX = mainWindow.x
                    initialWindowY = mainWindow.y
                    //                    console.log("Window Position -> x =", mainWindow.x,
                    //                                ", y =", mainWindow.y,
                    //                                ", Mouse -> globalX =", mouse.globalX, ", globalY =", mouse.globalY)

                }

                onPositionChanged: {
                    if (mouse.buttons & Qt.LeftButton) {
                        // Получаем дельту изменения координат
                        let deltaX = mouse.x - dragStartX
                        let deltaY = mouse.y - dragStartY

                        // Обновляем позицию окна
                        mainWindow.x = mainWindow.x + deltaX
                        mainWindow.y = mainWindow.y + deltaY
                    }
                }
            }
            /*****************************/
            //Кнопки управления окном
            ButtonFormControl{
//                x:1160
//                y:12
                anchors.right: parent.right
                onMinimizeClicked: {
                    console.log("Minimize button clicked")
                    // Добавьте действие для минимизации окна
                    onClicked: mainWindow.showMinimized()
                }

                onMaximizeClicked: {
                    console.log("Maximize button clicked")
                    // Добавьте действие для максимизации окна
                    if (mainWindow.visibility === Window.Maximized) {
                                    mainWindow.showNormal()
                                    mainWindow.visibility = "▢"
                                } else {
                                    mainWindow.showMaximized()
                                    mainWindow.visibility = "❐"
                                }

                                mainWindow.visibility === Window.Maximized ? "❐" : "▢"

                }

                onCloseClicked: {
                    console.log("Close button clicked")
                    // Добавьте действие для закрытия окна
                    Qt.quit()
                }
            }
            //            Row {
            //                anchors.verticalCenter: parent.verticalCenter
            //                anchors.right: parent.right
            //                anchors.rightMargin: 10
            //                spacing: 10

            //                // Кнопка свернуть
            //                Button {
            //                    text: "_"
            //                    width: 30
            //                    height: 30
            //                    onClicked: mainWindow.showMinimized()
            //                }

            //                // Кнопка развернуть/восстановить
            //                Button {
            //                    text: mainWindow.visibility === Window.Maximized ? "❐" : "▢"
            //                    //text: mainWindow.visibility = "▢"
            //                    width: 30
            //                    height: 30
            //                    onClicked: {
            //                        if (mainWindow.visibility === Window.Maximized) {
            //                            mainWindow.showNormal()
            //                            mainWindow.visibility = "▢"
            //                        } else {
            //                            mainWindow.showMaximized()
            //                            mainWindow.visibility = "❐"
            //                        }

            //                        mainWindow.visibility === Window.Maximized ? "❐" : "▢"
            //                    }
            //                }

            //                // Кнопка закрыть
            //                Button {
            //                    text: "✖"
            //                    width: 30
            //                    height: 30
            //                    onClicked: Qt.quit()
            //                }
            //            }
        }
        Rectangle {//Горизоньтальный разделитель
            width: parent.width
            height: 1
            color: Style.borderColor
            //radius: parent.radius
            anchors.top: titleBar.bottom
        }



        /**************** StatusBar *****************/
        Rectangle {//StatusBar
            id: statusBar
            width: parent.width
            height: 35
            anchors.bottom:  parent.bottom
            color: Style.backgroundColor
            border.color: Style.borderColor
            border.width: 1
            radius: 10

            Rectangle{
            width: 100
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            color: "transparent"
            Image {
                id:pictoConnectedPort
                width: 21
                height: 21
anchors.verticalCenter: parent.verticalCenter
anchors.left: parent.left
anchors.leftMargin: 10
                source: "qrc:/Image/pictoConnectedPort.png"
            }
            Text{
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: pictoConnectedPort.right
                anchors.leftMargin: 10
                text: "Port: " + comPort_part.comboBox.currentText
                color: Style.fontColorValue
                font.pixelSize: Style.fontSizeValue
                font.styleName: Style.fontValue
            }

            }

            Rectangle{//Изменение цветовой темы
                width: 100
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                color: "transparent"

                Image {
                    id:pictoTeme
                    width: 21
                    height: 21
    anchors.verticalCenter: parent.verticalCenter
    anchors.right:  parent.right
    anchors.rightMargin: 10
                    source: "qrc:/Image/pictoTeme.png"
                }

                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: pictoTeme.left
                    anchors.rightMargin: 10
                    text: "Theme:"
                    color: Style.fontColorValueStatusPanel
                    font.pixelSize: Style.fontSizeValueStatusPanel
                    font.styleName: Style.fontValueStatusPanel
                }
            }
        }
        /***********************************/


        // Контейнер для боковой панели
        Rectangle {
            id: sidePanel
            width: 241+17
            height: mainWindow.height - titleBar.height - statusBar.height
            color: Style.backgroundColor // Цвет фона панели
            border.color: Style.borderColor
            anchors.left: parent.left // Панель будет расположена рядом с toolPanel
            //anchors.top: titleBar.bottom
            anchors.bottom: statusBar.top
            visible: true // Панель изначально открыта
            z: 2

            ComPort {
                id:comPort_part
                width: 240-13-13//Посчитали из дизайна
                height: 63
                anchors.top: parent.top
                anchors.topMargin: 10 // Отступ сверху

            }

            PanelInfo{
                x: 17
                y: 152 - titleBar.height
            }


            CustomCheckBox {
                x:17
                y:302 - titleBar.height
                id: option_Close_after_reset
                text: "Close after reset"
                fontFamily: Style.fontValue // Тип шрифта
                fontSize: Style.fontSizeValue // Размер шрифта
                fontColor: Style.fontColorValue
                //checkedImage: "qrc:/Image/checkbox_checked.png"
                //uncheckedImage: "qrc:/Image/checkbox_unchecked.png"

                onToggled: console.log("Option 1:", checked)
            }

            ReadProgramm{
                x:17
                y:347 - titleBar.height
            }

            EdetButtons{
                x:17
                y: 404 - titleBar.height
            }


            ButtonsBlindsControl{
                x: 17
                y: 503 - titleBar.height
                buttonText: "Reset"
            }

            ButtonsBlindsControl{
                x: 17
                y: 651 - titleBar.height
                buttonText: "Reset all"
            }

            ButtonsBlindsControlGroup{
                x: 17
                y: 799 - titleBar.height
            }
        }// Контейнер для боковой панели




        //Рабочая область
        Rectangle{
            id: workPanel
            width: !!sidePanel.visible ? parent.width-sidePanel.width : parent.width//parent.width-sidePanel.width
            height: parent.height - titleBar.height - statusBar.height
            color: Style.backgroundColor
            border.width: 1
            border.color: Style.borderColor
            anchors.top: titleBar.bottom

            x: !!sidePanel.visible ?  sidePanel.width : 0

            ButtonScanID{
                id: buttonScanID
                x:269 - sidePanel.width
                y:61 - 47
            }

            Rectangle{

                id:tablePanel
                width: workPanel.width
                //height: 300
                height: parent.height - y
                anchors.top: buttonScanID.bottom   // Привязка к нижней стороне кнопки
                anchors.topMargin: 5
                color: Style.backgroundColor
                border.width: 1
                border.color: Style.borderColor
                   CustomTable{

                   }

            }

        }

    }

}
