import QtQuick 2.4

Rectangle {
    id: button
    width: 42
    height: 42
    color: "transparent"

    property alias defaultImage: buttonImage.defaultSource
    property alias hoverImage: buttonImage.hoverSource
    property alias pressedImage: buttonImage.pressedSource

    signal clicked()

    // Состояния кнопки
    Image {
        id: buttonImage
        anchors.fill: parent
        source: defaultSource

        property string defaultSource: ""
        property string hoverSource: ""
        property string pressedSource: ""
    }

//    MouseArea {
//        anchors.fill: parent
//        hoverEnabled: true
//        cursorShape: Qt.PointingHandCursor

//        onClicked: button.clicked()

//        onEntered: buttonImage.source = buttonImage.hoverSource
//        onExited: buttonImage.source = buttonImage.defaultSource
//        onPressed: buttonImage.source = buttonImage.pressedSource
//        onReleased: buttonImage.source = buttonImage.hoverSource
//    }

    MouseArea {


        anchors.fill: buttonImage
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        // Это выполняем в коде
         onClicked: button.clicked() // Вызываем сигнал clicked()

        onReleased: {
            buttonImage.source = buttonImage.hoverSource  // Изображение при наведении
            console.log("buttonImage: onReleased")
        }

        onPressed: {
            buttonImage.source = buttonImage.pressedSource  // Когда кнопка нажата
            console.log("buttonImage: onPressed")
        }

        onExited: {

           buttonImage.source = buttonImage.defaultSource  // Когда мышка покидает кнопку
        console.log("buttonImage: onExited")

        }

        onEntered: {
           buttonImage.source = buttonImage.hoverSource  // Когда мышка наводится
        console.log("buttonImage: onEntered")
        }
    }
}
