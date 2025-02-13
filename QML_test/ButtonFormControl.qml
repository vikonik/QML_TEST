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
            MouseArea {//Здесь так
                anchors.fill: parent
                onClicked: {
                    console.log("button_minimizeClicked clicked !111");
                   minimizeClicked()  // Сигнал передается наверх
                }
            }

        }
        CustomButton{
            width: 12
            height: 12
            color: "transparent"
            defaultImage: "qrc:/Image/buttonsFotmControl/buttonFormMax.png"
            hoverImage: "qrc:/Image/buttonsFotmControl/buttonFormMax.png"
            pressedImage: "qrc:/Image/buttonsFotmControl/buttonFormMax.png"
            onClicked: maximizeClicked()
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("button_maximizeClicked clicked !111");
                   maximizeClicked()  // Сигнал передается наверх
                }
            }

        }
        CustomButton{
            width: 12
            height: 12
            color: "transparent"
            defaultImage: "qrc:/Image/buttonsFotmControl/buttonFormClose.png"
            hoverImage: "qrc:/Image/buttonsFotmControl/buttonFormClose.png"
            pressedImage: "qrc:/Image/buttonsFotmControl/buttonFormClose.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("button_Close clicked !111");
                   closeClicked()  // Сигнал передается наверх
                }
            }
        }
    }
}
