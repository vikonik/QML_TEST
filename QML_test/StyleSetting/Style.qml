pragma Singleton
import QtQuick 2.0

QtObject {
    property  bool isDarkTheme: true
    readonly property color backgroundColor: isDarkTheme ? "#272727" : "#121212"
    readonly property color borderColor: isDarkTheme ? "#424242" : "#121212"

    //Цвета для кнопок Reset
    readonly property color buttonHoverBackgroundColor: isDarkTheme ? "#2A2A2A" : "#121212"
    readonly property color buttonHoverBorderColor: isDarkTheme ? "#909090" : "#121212"
    readonly property color buttonHoverTextrColor: isDarkTheme ? "#909090" : "#121212"
    readonly property color buttonDefaultTextrColor: isDarkTheme ? "#636363" : "#121212"

    readonly property color buttonGroupConrolBackgroundColor: isDarkTheme ? "#5B5B5B" : "#121212"

    // Свойства шрифта для Label
    readonly property string fontLabel: "Roboto-Regular" // Укажите желаемый шрифт
    readonly property int fontSizeLabel: 14
    readonly property color fontColorLabel: isDarkTheme ? "#919191" : "#FF0000"

    // Свойства шрифта для Значений
    readonly property string fontValue: "Roboto-Regular" // Укажите желаемый шрифт
    readonly property int fontSizeValue: 16
    readonly property color fontColorValue: isDarkTheme ? "#FFFFFF" : "#000000"

    // Свойства шрифта для панели состояния

    readonly property string fontValueStatusPanel: "Roboto-Medium" // Укажите желаемый шрифт
    readonly property int fontSizeValueStatusPanel: 12
    readonly property color fontColorValueStatusPanel: isDarkTheme ? "#9D9D9D" : "#000000"

    // Добавьте эти свойства в ваш файл стилей
    readonly property color headerColor: "#3a3a3a"
    readonly property color selectedRowColor: "#1e3a5f"
    readonly property color rowEvenColor: "#2a2a2a"
    readonly property color rowOddColor: "#222222"
    readonly property color editBorderColor: "#4a76b8"
    readonly property color textColor: "#ffffff"
}
