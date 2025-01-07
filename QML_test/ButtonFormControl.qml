import QtQuick 2.0

Rectangle {
    width:110
    height: 22
    color: "transparent"
anchors.right: parent.right
anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        signal minimizeClicked()
        signal maximizeClicked()
        signal closeClicked()

        Row{
        spacing: 30
anchors.verticalCenter: parent.verticalCenter
        CustomButton{
            id: buttonMinimized
        width: 12
        height: 2
        anchors.verticalCenter: parent.verticalCenter
 color: "transparent"
        defaultImage: "qrc:/Image/buttonsFotmControl/buttonFormHide.png"
        hoverImage: "qrc:/Image/buttonsFotmControl/buttonFormHide.png"
        pressedImage: "qrc:/Image/buttonsFotmControl/buttonFormHide.png"
        onClicked: minimizeClicked()
        }
        CustomButton{
            width: 12
            height: 12
 color: "transparent"
            defaultImage: "qrc:/Image/buttonsFotmControl/buttonFormMax.png"
            hoverImage: "qrc:/Image/buttonsFotmControl/buttonFormMax.png"
            pressedImage: "qrc:/Image/buttonsFotmControl/buttonFormMax.png"
        onClicked: maximizeClicked()
        }
        CustomButton{
            width: 12
            height: 12
 color: "transparent"

            defaultImage: "qrc:/Image/buttonsFotmControl/buttonFormClose.png"
            hoverImage: "qrc:/Image/buttonsFotmControl/buttonFormClose.png"
            pressedImage: "qrc:/Image/buttonsFotmControl/buttonFormClose.png"
        onClicked: closeClicked()
        }


    }

}
