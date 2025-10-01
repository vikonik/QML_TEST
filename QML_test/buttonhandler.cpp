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
        {"button_Read", [this]() { handleReadButton(); }}, // Добавляем обработчик для button_Read
        {"button_Programm", [this]() { handleProgramButton(); }}
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

/**/
void ButtonHandler::handleProgramButton()
{
    if (!m_tableController || !m_tableController->model()) {
        qDebug() << "TableController или Model не установлены!";
        return;
    }

    int selectedRow = m_tableController->selectedRow();
    if (selectedRow < 0) {
        qDebug() << "Не выбрана строка для программирования!";
        return;
    }

    // Получаем информацию о типе строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);

    QString deviceData;

    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        deviceData = serializeOneChannelData();
    }
    else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        deviceData = serializeSixChannelData();
    }
    else {
        qDebug() << "Неизвестный тип устройства";
        return;
    }

    qDebug() << "Данные для программирования:" << deviceData;
    emit signalProgramRequest(deviceData);
}

QString ButtonHandler::serializeOneChannelData() const
{
    if (!m_tableController /*|| !m_tableController->model()*/) {
        return QString();
    }

    int selectedRow = m_tableController->selectedRow();
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);

    if (rowInfo.deviceType != TableModel::OneChannelDevice) {
        return QString();
    }

    QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
    if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
        return QString();
    }

    const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];

    // Сериализуем данные в строку (можно использовать JSON, XML или простой формат)
    QString data ;
    data.append("\r\n>");
    data.append(device.address);
    data.append(device.type);
    data.append(device.flag);
    data.append(device.versionFW);

    data.append(device.group_1);
    data.append(device.group_2);
    data.append(device.group_3);
    data.append(device.group_4);

    data.append(device.steps);
    data.append(device.tiltAngle);
    data.append(device.hight);
    data.append(device.tiltOnly);

    data.append(device.SAR);
    data.append(device.currentPosition);
    data.append(device.error);
    data.append(device.voltage);

    data.append(device.day);
    data.append(device.month);
    data.append(device.year);

    data.append(device.BR);
    data.append(device.dir);
    data.append("<");


    return data;
}

QString ButtonHandler::serializeSixChannelData() const
{
    if (!m_tableController /*|| !m_tableController->model()*/) {
        return QString();
    }

    int selectedRow = m_tableController->selectedRow();
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);

    if (rowInfo.deviceType != TableModel::SixChannelDevice) {
        return QString();
    }

    QVector<SixChanel_t> sixChannelData = m_tableController->model()->getSixChanelData();
    if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= sixChannelData.size()) {
        return QString();
    }

    const SixChanel_t &device = sixChannelData[rowInfo.deviceIndex];

    // Сериализуем данные в строку
//    QString data = QString("TYPE=SIXCHANNEL;"
//                          "ADDR=%1;FW=%2;DATE=%3.%4.%5;"
//                          "CH1_GROUPS=%6,%7,%8,%9;CH1_HEIGHT=%10;CH1_ANGLE=%11;CH1_TILTONLY=%12;CH1_DIR=%13;"
//                          "CH2_GROUPS=%14,%15,%16,%17;CH2_HEIGHT=%18;CH2_ANGLE=%19;CH2_TILTONLY=%20;CH2_DIR=%21")
//        .arg(device.address)
//        .arg(device.versionFW)
//        .arg(device.day).arg(device.month).arg(device.year)
//        .arg(device.chanel_1.group_1).arg(device.chanel_1.group_2).arg(device.chanel_1.group_3).arg(device.chanel_1.group_4)
//        .arg(device.chanel_1.hight).arg(device.chanel_1.endangle).arg(device.chanel_1.tiltOnly).arg(device.chanel_1.dir)
//        .arg(device.chanel_2.group_1).arg(device.chanel_2.group_2).arg(device.chanel_2.group_3).arg(device.chanel_2.group_4)
//        .arg(device.chanel_2.hight).arg(device.chanel_2.endangle).arg(device.chanel_2.tiltOnly).arg(device.chanel_2.dir);

    QString data ;
    // --- Общие поля ---
    data.append("\r\n>");
    data.append(device.address);
    data.append(device.type);
    data.append(device.flag);
    data.append(device.versionFW);

    data.append(device.day);
    data.append(device.month);
    data.append(device.year);

    data.append(device.BR);
    data.append("<");
    // --- Chanel_1 ---
    data.append("\r\n>");
    data.append(device.chanel_1.address);
    data.append(device.chanel_1.chanel);
    data.append(device.chanel_1.group_1);
    data.append(device.chanel_1.group_2);
    data.append(device.chanel_1.group_3);
    data.append(device.chanel_1.group_4);
    data.append(device.chanel_1.steps);
    data.append(device.chanel_1.endangle);
    data.append(device.chanel_1.hight);
    data.append(device.chanel_1.tiltOnly);
    data.append(device.chanel_1.SAR);
    data.append(device.chanel_1.currentPosition);
    data.append(device.chanel_1.error);
    data.append(device.chanel_1.dir);
    data.append("<");
    // --- Chanel_2 ---
    data.append("\r\n>");
    data.append(device.chanel_2.address);
    data.append(device.chanel_2.chanel);
    data.append(device.chanel_2.group_1);
    data.append(device.chanel_2.group_2);
    data.append(device.chanel_2.group_3);
    data.append(device.chanel_2.group_4);
    data.append(device.chanel_2.steps);
    data.append(device.chanel_2.endangle);
    data.append(device.chanel_2.hight);
    data.append(device.chanel_2.tiltOnly);
    data.append(device.chanel_2.SAR);
    data.append(device.chanel_2.currentPosition);
    data.append(device.chanel_2.error);
    data.append(device.chanel_2.dir);
    data.append("<");
    // --- Chanel_3 ---
    data.append("\r\n>");
    data.append(device.chanel_3.address);
    data.append(device.chanel_3.chanel);
    data.append(device.chanel_3.group_1);
    data.append(device.chanel_3.group_2);
    data.append(device.chanel_3.group_3);
    data.append(device.chanel_3.group_4);
    data.append(device.chanel_3.steps);
    data.append(device.chanel_3.endangle);
    data.append(device.chanel_3.hight);
    data.append(device.chanel_3.tiltOnly);
    data.append(device.chanel_3.SAR);
    data.append(device.chanel_3.currentPosition);
    data.append(device.chanel_3.error);
    data.append(device.chanel_3.dir);
    data.append("<");
    // --- Chanel_4 ---
    data.append("\r\n>");
    data.append(device.chanel_4.address);
    data.append(device.chanel_4.chanel);
    data.append(device.chanel_4.group_1);
    data.append(device.chanel_4.group_2);
    data.append(device.chanel_4.group_3);
    data.append(device.chanel_4.group_4);
    data.append(device.chanel_4.steps);
    data.append(device.chanel_4.endangle);
    data.append(device.chanel_4.hight);
    data.append(device.chanel_4.tiltOnly);
    data.append(device.chanel_4.SAR);
    data.append(device.chanel_4.currentPosition);
    data.append(device.chanel_4.error);
    data.append(device.chanel_4.dir);
    data.append("<");
    // --- Chanel_5 ---
    data.append("\r\n>");
    data.append(device.chanel_5.address);
    data.append(device.chanel_5.chanel);
    data.append(device.chanel_5.group_1);
    data.append(device.chanel_5.group_2);
    data.append(device.chanel_5.group_3);
    data.append(device.chanel_5.group_4);
    data.append(device.chanel_5.steps);
    data.append(device.chanel_5.endangle);
    data.append(device.chanel_5.hight);
    data.append(device.chanel_5.tiltOnly);
    data.append(device.chanel_5.SAR);
    data.append(device.chanel_5.currentPosition);
    data.append(device.chanel_5.error);
    data.append(device.chanel_5.dir);
    data.append("<");
    // --- Chanel_6 ---
    data.append("\r\n>");
    data.append(device.chanel_6.address);
    data.append(device.chanel_6.chanel);
    data.append(device.chanel_6.group_1);
    data.append(device.chanel_6.group_2);
    data.append(device.chanel_6.group_3);
    data.append(device.chanel_6.group_4);
    data.append(device.chanel_6.steps);
    data.append(device.chanel_6.endangle);
    data.append(device.chanel_6.hight);
    data.append(device.chanel_6.tiltOnly);
    data.append(device.chanel_6.SAR);
    data.append(device.chanel_6.currentPosition);
    data.append(device.chanel_6.error);
    data.append(device.chanel_6.dir);
data.append("<");

    // Можно добавить остальные каналы по аналогии

    return data;
}
