import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    width: parent.width
    height: parent.height

    // Вертикальное расположение элементов
    ColumnLayout {
        anchors.fill: parent
        spacing: 20
        Layout.margins: 20

        // Поле ввода
        TextField {
            placeholderText: "Введите текст"
            Layout.fillWidth: true
        }

        // Чекбокс
        CheckBox {
            text: "Активировать опцию"
            Layout.fillWidth: true
        }

        // Комбобокс
        ComboBox {
            model: ["Опция 1", "Опция 2", "Опция 3"]
            Layout.fillWidth: true
        }

        // Кнопка
        Button {
            text: "Подтвердить"
            Layout.fillWidth: true
            onClicked: console.log("Подтверждено!")
        }

        // Кнопка
        Button {
            text: "Отмена"
            Layout.fillWidth: true
            onClicked: console.log("Отменено!")
        }
    }
}
