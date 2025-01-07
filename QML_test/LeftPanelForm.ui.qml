import QtQuick 2.4

Rectangle {
    x: 0
    width: parent
    height: 812
    color: "#272727"
    border.color: "#424242"
    border.width: 1
    ComPort {
        anchors.fill: parent // Занимает всю площадь панели
    }
}
