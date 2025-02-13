import QtQuick 2.4

Rectangle {
    id: button
    width: 42
    height: 42
    color: "transparent"

    property alias defaultImage: buttonImage.defaultSource
    property alias hoverImage: buttonImage.hoverSource
    property alias pressedImage: buttonImage.pressedSource
    property string buttonId: ""  // Идентификатор кнопки
    signal clicked(string buttonName)  // Передаем имя кнопки

    // Состояния кнопки
    Image {
        id: buttonImage
        anchors.fill: parent
        source: defaultSource

        property string defaultSource: ""
        property string hoverSource: ""
        property string pressedSource: ""
    }

    MouseArea {


        anchors.fill: buttonImage
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        // Это выполняем в коде
        onClicked: {
            console.log("Button clicked !!:", buttonId)
            buttonHandler.onButtonClicked(buttonId)  // Передаем objectName
        }

        onReleased: {
            buttonImage.source = buttonImage.hoverSource  // Изображение при наведении
//            console.log("buttonImage: onReleased")
        }

        onPressed: {
            buttonImage.source = buttonImage.pressedSource  // Когда кнопка нажата
//           console.log("buttonImage: onPressed")
        }

        onExited: {

           buttonImage.source = buttonImage.defaultSource  // Когда мышка покидает кнопку
//        console.log("buttonImage: onExited")

        }

        onEntered: {
           buttonImage.source = buttonImage.hoverSource  // Когда мышка наводится
//        console.log("buttonImage: onEntered")
        }
    }
}
