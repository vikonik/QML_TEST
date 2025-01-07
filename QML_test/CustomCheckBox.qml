import QtQuick 2.4

Rectangle {
    id: customCheckbox
    width: 200
    height: 40
    color: "transparent"

    property alias text: checkboxLabel.text
    property alias checked: checkboxState.checked
    property alias checkedImage: checkboxState.checkedSource
    property alias uncheckedImage: checkboxState.uncheckedSource

    property string fontFamily: "Arial"
    property int fontSize: 14
    property color fontColor: "black"

    signal toggled(bool checked)

    Row {
        spacing: 10
        anchors.fill: parent
        anchors.margins: 5

        // Картинка для состояния
        Image {
            id: checkboxState
            width: 24
            height: 24
            source: uncheckedSource

            property bool checked: false
            property string checkedSource: "qrc:/Image/checkBox/checkbox_checked.png"
            property string uncheckedSource: "qrc:/Image/checkBox/checkbox_unchecked.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    checkboxState.checked = !checkboxState.checked;
                    checkboxState.source = checkboxState.checked ? checkboxState.checkedSource : checkboxState.uncheckedSource;
                    checkbox.toggled(checkboxState.checked);
                }
            }
        }

        // Текст рядом с чекбоксом
        Text {
            id: checkboxLabel
            text: customCheckbox.text
            color: customCheckbox.fontColor
            font.family: customCheckbox.fontFamily
            font.pixelSize: customCheckbox.fontSize
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    checkboxState.checked = !checkboxState.checked;
                    checkboxState.source = checkboxState.checked ? checkboxState.checkedSource : checkboxState.uncheckedSource;
                    checkbox.toggled(checkboxState.checked);
                }
            }
        }
    }
}

