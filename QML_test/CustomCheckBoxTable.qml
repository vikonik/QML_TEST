// CustomCheckBox.qml
import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: root
    property bool checked: false
    signal toggled(bool checked)

    width: 20
    height: 20

    Image {
        id: checkboxImage
        anchors.fill: parent
        source: root.checked ? "qrc:/Image/checkBox/checkbox_checked.png" : "qrc:/Image/checkBox/checkbox_unchecked.png"
        fillMode: Image.PreserveAspectFit

        Behavior on source {
            PropertyAnimation { duration: 100 }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.checked = !root.checked
            root.toggled(root.checked)
        }
    }
}
