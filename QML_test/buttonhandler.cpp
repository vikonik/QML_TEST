/*
нажатие на кнопку вызовет onButtonClicked, аргументом будет ID нажатой кнопки
Определяем какая кнопка была нажата и выполняем соответствующее действие
*/
#include "buttonhandler.h"

ButtonHandler::ButtonHandler(QObject *parent) : QObject(parent) {}

void ButtonHandler::setTableController(TableController *controller)
{
    m_tableController = controller;
}

void ButtonHandler::onButtonClicked(const QString &buttonId) {
    qDebug() << "С++ Button clicked:" << buttonId;

    // Карта соответствия названий кнопок и функций-обработчиков
    static const QMap<QString, std::function<void()>> actions = {
        {"button_ScanID", [this]() {  emit signalSkanID(); qDebug() << "Отправлена команда SkanID"; }},
        {"rectButtonConnect", [this]() { emit signalConnect();  qDebug() << "Подключить порт"; }},
        {"rectButtonDisconnect", [this]() { emit signalDisconnect(); qDebug() << "Отключить порт"; }},
        {"button_Read", [this]() { handleReadButton(); }}  // Добавляем обработчик для button_Read

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
void ButtonHandler::print(){
    qDebug() << "С++ Button clicked: print";
emit signalConnect();
}
/*
 *  Метод для обработки кнопки Read
 */
void ButtonHandler::handleReadButton()
{
    if (!m_tableController) {
        qDebug() << "TableController не установлен!";
        return;
    }

    // Получаем Serial ID из TableController
    QString serialID = m_tableController->serialText();
    qDebug() << "Получен Serial ID:" << serialID;

    // Излучаем сигнал с полученным Serial ID
    emit signalReadRequest(serialID);
}
