/*
нажатие на кнопку вызовет onButtonClicked, аргументом будет ID нажатой кнопки
Определяем какая кнопка была нажата и выполняем соответствующее действие
*/
#include "buttonhandler.h"

ButtonHandler::ButtonHandler(QObject *parent) : QObject(parent) {}

void ButtonHandler::onButtonClicked(const QString &buttonId) {
    qDebug() << "С++ Button clicked:" << buttonId;

    // Карта соответствия названий кнопок и функций-обработчиков
    static const QMap<QString, std::function<void()>> actions = {
        {"button_ScanID", []() {  qDebug() << "Запуск процесса"; }}
//        {"stop", [this]() { stopProcess(); }},
//        {"reset", [this]() { resetProcess(); }}
    };

    // Ищем кнопку в карте и вызываем соответствующую функцию
    auto it = actions.find(buttonId);
    if (it != actions.end()) {
        it.value()(); // Вызов функции
    } else {
        qDebug() << "Неизвестная кнопка";
    }
}

/**/
