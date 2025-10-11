/*
нажатие на кнопку вызовет onButtonClicked, аргументом будет ID нажатой кнопки
Определяем какая кнопка была нажата и выполняем соответствующее действие
*/
#include "buttonhandler.h"
#include "dataStruct.h"
#include "tablecontroller.h"
#include <QFileDialog>
#include <QMessageBox>

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
        {"button_Programm", [this]() { handleProgramButton(); }},
        {"button_DefaultSetup", [this]() { handleDefaultSetupButton(); }},
        {"button_DownloadSetup", [this]() { loadFromFileDialog(); }},
        {"button_Copy", [this]() { handleCopyButton(); }},
        {"button_Paste", [this]() { handlePasteButton(); }},

        {"buttonsBlindsControlbutton_UP", [this]()           { handlebuttonsBlindsControlbutton_UP(); }},
        {"buttonsBlindsControlbutton_UpLeft", [this]()       { handlebuttonsBlindsControlbutton_UpLeft(); }},
        {"buttonsBlindsControlbutton_Stop", [this]()         { handlebuttonsBlindsControlbutton_Stop(); }},
        {"buttonsBlindsControlbutton_Down", [this]()         { handlebuttonsBlindsControlbutton_Down(); }},
        {"buttonsBlindsControlbutton_DownRight", [this]()    { handlebuttonsBlindsControlbutton_DownRight(); }},
        {"buttonsBlindsControlAllbutton_UP", [this]()        { handlebuttonsBlindsControlAllbutton_UP(); }},
        {"buttonsBlindsControlAllbutton_UpLeft", [this]()    { handlebuttonsBlindsControlAllbutton_UpLeft(); }},
        {"buttonsBlindsControlAllbutton_Stop", [this]()      { handlebuttonsBlindsControlAllbutton_Stop(); }},
        {"buttonsBlindsControlAllbutton_Down", [this]()      { handlebuttonsBlindsControlAllbutton_Down(); }},
        {"buttonsBlindsControlAllbutton_DownRight", [this]() { handlebuttonsBlindsControlAllbutton_DownRight(); }}

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

/**/
QString ButtonHandler::serializeOneChannelData() const
{
    if (!m_tableController /*|| !m_tableController->model()*/) {
        return QString();
    }

    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);

    if (rowInfo.deviceType != TableModel::OneChannelDevice) {
        return QString();
    }

    QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
    if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
        return QString();
    }

    const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];//Получаем данные из выбранной строки

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


/*
здесь устанавливаем значеия по умолчанию
*/
void ButtonHandler::handleDefaultSetupButton(){
    if (!m_tableController) {
           qWarning() << "Cannot update serial value: model not set, no row selected, or data parser not set";
           return;
       }

    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        // Обновление одноканального устройства
        QVector<OneChanel_t> devices = m_tableController->model()->getOneChanelData();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные
            //devices[rowInfo.deviceIndex].address = newValue;
            devices[rowInfo.deviceIndex].group_1 = oneChanelDefaulsSetting.group_1;
            devices[rowInfo.deviceIndex].group_2 = oneChanelDefaulsSetting.group_2;
            devices[rowInfo.deviceIndex].group_3 = oneChanelDefaulsSetting.group_3;
            devices[rowInfo.deviceIndex].group_4 = oneChanelDefaulsSetting.group_4;
            devices[rowInfo.deviceIndex].hight = oneChanelDefaulsSetting.hight;
            devices[rowInfo.deviceIndex].tiltAngle = oneChanelDefaulsSetting.tiltAngle;
            devices[rowInfo.deviceIndex].tiltOnly = oneChanelDefaulsSetting.tiltOnly;
            devices[rowInfo.deviceIndex].dir = oneChanelDefaulsSetting.dir;
            m_tableController->model()->loadOneChanelData(devices);

        }
    }
    else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        // Обновление шестиканального устройства

        QVector<SixChanel_t> devices = m_tableController->model()->getSixChanelData();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные (только для первого канала)
            //!!!devices[rowInfo.deviceIndex].address = newValue;
        devices[rowInfo.deviceIndex].chanel_1.group_1   = sixChanelDefaulsSetting.chanel_1.group_1;
        devices[rowInfo.deviceIndex].chanel_1.group_2   = sixChanelDefaulsSetting.chanel_1.group_2;
        devices[rowInfo.deviceIndex].chanel_1.group_3   = sixChanelDefaulsSetting.chanel_1.group_3;
        devices[rowInfo.deviceIndex].chanel_1.group_4   = sixChanelDefaulsSetting.chanel_1.group_4;
        devices[rowInfo.deviceIndex].chanel_1.hight     = sixChanelDefaulsSetting.chanel_1.hight;
        devices[rowInfo.deviceIndex].chanel_1.endangle  = sixChanelDefaulsSetting.chanel_1.tiltAngle;
        devices[rowInfo.deviceIndex].chanel_1.tiltOnly  = sixChanelDefaulsSetting.chanel_1.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_1.dir       = sixChanelDefaulsSetting.chanel_1.dir;

        devices[rowInfo.deviceIndex].chanel_2.group_1   = sixChanelDefaulsSetting.chanel_2.group_1;
        devices[rowInfo.deviceIndex].chanel_2.group_2   = sixChanelDefaulsSetting.chanel_2.group_2;
        devices[rowInfo.deviceIndex].chanel_2.group_3   = sixChanelDefaulsSetting.chanel_2.group_3;
        devices[rowInfo.deviceIndex].chanel_2.group_4   = sixChanelDefaulsSetting.chanel_2.group_4;
        devices[rowInfo.deviceIndex].chanel_2.hight     = sixChanelDefaulsSetting.chanel_2.hight;
        devices[rowInfo.deviceIndex].chanel_2.endangle  = sixChanelDefaulsSetting.chanel_2.tiltAngle;
        devices[rowInfo.deviceIndex].chanel_2.tiltOnly  = sixChanelDefaulsSetting.chanel_2.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_2.dir       = sixChanelDefaulsSetting.chanel_2.dir;

        devices[rowInfo.deviceIndex].chanel_3.group_1   = sixChanelDefaulsSetting.chanel_3.group_1;
        devices[rowInfo.deviceIndex].chanel_3.group_2   = sixChanelDefaulsSetting.chanel_3.group_2;
        devices[rowInfo.deviceIndex].chanel_3.group_3   = sixChanelDefaulsSetting.chanel_3.group_3;
        devices[rowInfo.deviceIndex].chanel_3.group_4   = sixChanelDefaulsSetting.chanel_3.group_4;
        devices[rowInfo.deviceIndex].chanel_3.hight     = sixChanelDefaulsSetting.chanel_3.hight;
        devices[rowInfo.deviceIndex].chanel_3.endangle  = sixChanelDefaulsSetting.chanel_3.tiltAngle;
        devices[rowInfo.deviceIndex].chanel_3.tiltOnly  = sixChanelDefaulsSetting.chanel_3.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_3.dir       = sixChanelDefaulsSetting.chanel_3.dir;

        devices[rowInfo.deviceIndex].chanel_4.group_1   = sixChanelDefaulsSetting.chanel_4.group_1;
        devices[rowInfo.deviceIndex].chanel_4.group_2   = sixChanelDefaulsSetting.chanel_4.group_2;
        devices[rowInfo.deviceIndex].chanel_4.group_3   = sixChanelDefaulsSetting.chanel_4.group_3;
        devices[rowInfo.deviceIndex].chanel_4.group_4   = sixChanelDefaulsSetting.chanel_4.group_4;
        devices[rowInfo.deviceIndex].chanel_4.hight     = sixChanelDefaulsSetting.chanel_4.hight;
        devices[rowInfo.deviceIndex].chanel_4.endangle  = sixChanelDefaulsSetting.chanel_4.tiltAngle;
        devices[rowInfo.deviceIndex].chanel_4.tiltOnly  = sixChanelDefaulsSetting.chanel_4.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_4.dir       = sixChanelDefaulsSetting.chanel_4.dir;

        devices[rowInfo.deviceIndex].chanel_5.group_1   = sixChanelDefaulsSetting.chanel_5.group_1;
        devices[rowInfo.deviceIndex].chanel_5.group_2   = sixChanelDefaulsSetting.chanel_5.group_2;
        devices[rowInfo.deviceIndex].chanel_5.group_3   = sixChanelDefaulsSetting.chanel_5.group_3;
        devices[rowInfo.deviceIndex].chanel_5.group_4   = sixChanelDefaulsSetting.chanel_5.group_4;
        devices[rowInfo.deviceIndex].chanel_5.hight     = sixChanelDefaulsSetting.chanel_5.hight;
        devices[rowInfo.deviceIndex].chanel_5.endangle  = sixChanelDefaulsSetting.chanel_5.tiltAngle;
        devices[rowInfo.deviceIndex].chanel_5.tiltOnly  = sixChanelDefaulsSetting.chanel_5.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_5.dir       = sixChanelDefaulsSetting.chanel_5.dir;

        devices[rowInfo.deviceIndex].chanel_6.group_1   = sixChanelDefaulsSetting.chanel_6.group_1;
        devices[rowInfo.deviceIndex].chanel_6.group_2   = sixChanelDefaulsSetting.chanel_6.group_2;
        devices[rowInfo.deviceIndex].chanel_6.group_3   = sixChanelDefaulsSetting.chanel_6.group_3;
        devices[rowInfo.deviceIndex].chanel_6.group_4   = sixChanelDefaulsSetting.chanel_6.group_4;
        devices[rowInfo.deviceIndex].chanel_6.hight     = sixChanelDefaulsSetting.chanel_6.hight;
        devices[rowInfo.deviceIndex].chanel_6.endangle  = sixChanelDefaulsSetting.chanel_6.tiltAngle;
        devices[rowInfo.deviceIndex].chanel_6.tiltOnly  = sixChanelDefaulsSetting.chanel_6.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_6.dir       = sixChanelDefaulsSetting.chanel_6.dir;


            // Здесь нужно добавить метод в DataParser для обновления шестиканальных устройств
        m_tableController->model()->loadSixChanelData(devices);
        }
    }


   m_tableController->model()->resortTable();


//    qDebug() << "Updated serial value to:" << newValue << "for row:" << m_selectedRow << "m_serialText " << m_serialText;

}


/*
Загрузка из файла
*/
void ButtonHandler::loadFromFileDialog()
{
    // Вызываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Выберите файл с данными устройств",
        QDir::homePath(),
        "Data Files (*.csv *.dat *.txt);;All Files (*.*)"
    );

    if (filePath.isEmpty()) {
        qDebug() << "Файл не выбран";
        return;
    }

    qDebug() << "Выбран файл:" << filePath;

    // Отправляем сигнал с путем к файлу
   // emit signalLoadFromFile(filePath);
    loadDataFromFile(filePath);
}

/*
Загружаем данные из файла в выбранную строку
*/
bool ButtonHandler::loadDataFromFile(const QString &filePath)
{

//    QMessageBox::information(nullptr, "Успех", "Данные успешно сохранены");
//    QMessageBox::warning(nullptr, "Внимание", "Не все поля заполнены корректно");
//    QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к устройству");
    QFile file(filePath);
    QTextStream in(&file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for reading:" << filePath;
        return false;
    }


    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);//Узнали тип контроллера


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        // Обновление одноканального устройства
        QVector<OneChanel_t> devices = m_tableController->model()->getOneChanelData();//Полчили нужную строку

        int lineNumber = 0;
        OneChanel_t oneChannelSeviceNewData;//данные из файла находятся здесь

        while (!in.atEnd()) {
            QString line = in.readLine();
            lineNumber++;

            // Пропускаем пустые строки и комментарии
            if (line.trimmed().isEmpty() || line.startsWith('#')) {
                continue;
            }

            // Определяем тип устройства по префиксу
            if (line.startsWith("ONECHANNEL:")) {
                  if (!parseOneChannelLine(line, oneChannelSeviceNewData)) {
                    qWarning() << "Failed to parse one-channel device at line" << lineNumber;
                }
            }
            else{
                QMessageBox::critical(nullptr, "Ошибка", "Тип файла не соответствует выбранному контроллеру");
                file.close();
                return false;
            }
        }//in.atEnd()

        file.close();


        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные
            //devices[rowInfo.deviceIndex].address = newValue;
            devices[rowInfo.deviceIndex].group_1 = oneChannelSeviceNewData.group_1;
            devices[rowInfo.deviceIndex].group_2 = oneChannelSeviceNewData.group_2;
            devices[rowInfo.deviceIndex].group_3 = oneChannelSeviceNewData.group_3;
            devices[rowInfo.deviceIndex].group_4 = oneChannelSeviceNewData.group_4;
            devices[rowInfo.deviceIndex].hight = oneChannelSeviceNewData.hight;
            devices[rowInfo.deviceIndex].tiltAngle = oneChannelSeviceNewData.tiltAngle;
            devices[rowInfo.deviceIndex].tiltOnly = oneChannelSeviceNewData.tiltOnly;
            devices[rowInfo.deviceIndex].dir = oneChannelSeviceNewData.dir;
            m_tableController->model()->loadOneChanelData(devices);

        }
    }
    else if(rowInfo.deviceType == TableModel::SixChannelDevice){
        QVector<SixChanel_t> devices = m_tableController->model()->getSixChanelData();
        int lineNumber = 0;
        SixChanel_t sixChannelSeviceNewData;//данные из файла находятся здесь
        while (!in.atEnd()) {
            QString line = in.readLine();
            lineNumber++;

            // Пропускаем пустые строки и комментарии
            if (line.trimmed().isEmpty() || line.startsWith('#')) {
                continue;
            }

            // Определяем тип устройства по префиксу
            if (line.startsWith("SIXCHANNEL:")) {
                  if (!parseSixChannelLine(line, sixChannelSeviceNewData)) {
                    qWarning() << "Failed to parse six-channel device at line" << lineNumber;
                }
            }
            else{
                QMessageBox::critical(nullptr, "Ошибка", "Тип файла не соответствует выбранному контроллеру");
                file.close();
                return false;
            }
        }//in.atEnd()

        file.close();

         if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные (только для первого канала)
        devices[rowInfo.deviceIndex].chanel_1.group_1   = "9999";//sixChannelSeviceNewData.chanel_1.group_1;
        devices[rowInfo.deviceIndex].chanel_1.group_2   = sixChannelSeviceNewData.chanel_1.group_2;
        devices[rowInfo.deviceIndex].chanel_1.group_3   = sixChannelSeviceNewData.chanel_1.group_3;
        devices[rowInfo.deviceIndex].chanel_1.group_4   = sixChannelSeviceNewData.chanel_1.group_4;
        devices[rowInfo.deviceIndex].chanel_1.hight     = sixChannelSeviceNewData.chanel_1.hight;
        devices[rowInfo.deviceIndex].chanel_1.endangle  = sixChannelSeviceNewData.chanel_1.endangle;
        devices[rowInfo.deviceIndex].chanel_1.tiltOnly  = sixChannelSeviceNewData.chanel_1.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_1.dir       = sixChannelSeviceNewData.chanel_1.dir;

        devices[rowInfo.deviceIndex].chanel_2.group_1   = sixChannelSeviceNewData.chanel_2.group_1;
        devices[rowInfo.deviceIndex].chanel_2.group_2   = sixChannelSeviceNewData.chanel_2.group_2;
        devices[rowInfo.deviceIndex].chanel_2.group_3   = sixChannelSeviceNewData.chanel_2.group_3;
        devices[rowInfo.deviceIndex].chanel_2.group_4   = sixChannelSeviceNewData.chanel_2.group_4;
        devices[rowInfo.deviceIndex].chanel_2.hight     = sixChannelSeviceNewData.chanel_2.hight;
        devices[rowInfo.deviceIndex].chanel_2.endangle  = sixChannelSeviceNewData.chanel_2.endangle;
        devices[rowInfo.deviceIndex].chanel_2.tiltOnly  = sixChannelSeviceNewData.chanel_2.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_2.dir       = sixChannelSeviceNewData.chanel_2.dir;

        devices[rowInfo.deviceIndex].chanel_3.group_1   = sixChannelSeviceNewData.chanel_3.group_1;
        devices[rowInfo.deviceIndex].chanel_3.group_2   = sixChannelSeviceNewData.chanel_3.group_2;
        devices[rowInfo.deviceIndex].chanel_3.group_3   = sixChannelSeviceNewData.chanel_3.group_3;
        devices[rowInfo.deviceIndex].chanel_3.group_4   = sixChannelSeviceNewData.chanel_3.group_4;
        devices[rowInfo.deviceIndex].chanel_3.hight     = sixChannelSeviceNewData.chanel_3.hight;
        devices[rowInfo.deviceIndex].chanel_3.endangle  = sixChannelSeviceNewData.chanel_3.endangle;
        devices[rowInfo.deviceIndex].chanel_3.tiltOnly  = sixChannelSeviceNewData.chanel_3.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_3.dir       = sixChannelSeviceNewData.chanel_3.dir;

        devices[rowInfo.deviceIndex].chanel_4.group_1   = sixChannelSeviceNewData.chanel_4.group_1;
        devices[rowInfo.deviceIndex].chanel_4.group_2   = sixChannelSeviceNewData.chanel_4.group_2;
        devices[rowInfo.deviceIndex].chanel_4.group_3   = sixChannelSeviceNewData.chanel_4.group_3;
        devices[rowInfo.deviceIndex].chanel_4.group_4   = sixChannelSeviceNewData.chanel_4.group_4;
        devices[rowInfo.deviceIndex].chanel_4.hight     = sixChannelSeviceNewData.chanel_4.hight;
        devices[rowInfo.deviceIndex].chanel_4.endangle  = sixChannelSeviceNewData.chanel_4.endangle;
        devices[rowInfo.deviceIndex].chanel_4.tiltOnly  = sixChannelSeviceNewData.chanel_4.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_4.dir       = sixChannelSeviceNewData.chanel_4.dir;

        devices[rowInfo.deviceIndex].chanel_5.group_1   = sixChannelSeviceNewData.chanel_5.group_1;
        devices[rowInfo.deviceIndex].chanel_5.group_2   = sixChannelSeviceNewData.chanel_5.group_2;
        devices[rowInfo.deviceIndex].chanel_5.group_3   = sixChannelSeviceNewData.chanel_5.group_3;
        devices[rowInfo.deviceIndex].chanel_5.group_4   = sixChannelSeviceNewData.chanel_5.group_4;
        devices[rowInfo.deviceIndex].chanel_5.hight     = sixChannelSeviceNewData.chanel_5.hight;
        devices[rowInfo.deviceIndex].chanel_5.endangle  = sixChannelSeviceNewData.chanel_5.endangle;
        devices[rowInfo.deviceIndex].chanel_5.tiltOnly  = sixChannelSeviceNewData.chanel_5.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_5.dir       = sixChannelSeviceNewData.chanel_5.dir;

        devices[rowInfo.deviceIndex].chanel_6.group_1   = sixChannelSeviceNewData.chanel_6.group_1;
        devices[rowInfo.deviceIndex].chanel_6.group_2   = sixChannelSeviceNewData.chanel_6.group_2;
        devices[rowInfo.deviceIndex].chanel_6.group_3   = sixChannelSeviceNewData.chanel_6.group_3;
        devices[rowInfo.deviceIndex].chanel_6.group_4   = sixChannelSeviceNewData.chanel_6.group_4;
        devices[rowInfo.deviceIndex].chanel_6.hight     = sixChannelSeviceNewData.chanel_6.hight;
        devices[rowInfo.deviceIndex].chanel_6.endangle  = sixChannelSeviceNewData.chanel_6.endangle;
        devices[rowInfo.deviceIndex].chanel_6.tiltOnly  = sixChannelSeviceNewData.chanel_6.tiltOnly;
        devices[rowInfo.deviceIndex].chanel_6.dir       = sixChannelSeviceNewData.chanel_6.dir;


            // Здесь нужно добавить метод в DataParser для обновления шестиканальных устройств
            // m_dataParser->setSixChanelDevices(devices);

        m_tableController->model()->loadSixChanelData(devices);

    }
    }
    else{
        QMessageBox::critical(nullptr, "Ошибка", "Не выбрана стрка");
    }


m_tableController->model()->resortTable();//SerialID не меняется, поэтому можно и так)))

//    qDebug() << "Loaded" << m_oneChanelData.size() << "one-channel devices and"
//             << m_sixChanelData.size() << "six-channel devices from" << filePath;
    return true;
}

/**/
bool ButtonHandler::parseOneChannelLine(const QString &line, OneChanel_t &device)
{
    // Проверяем, что строка действительно начинается с SIXCHANNEL:
    if (!line.startsWith("ONECHANNEL:")) {
        qWarning() << "Invalid ONECHANNEL prefix in line:" << line;
        return false;
    }
    // Убираем префикс "ONECHANNEL:"
    QString data = line.mid(11); // Длина "ONECHANNEL:"

    // Парсим данные (пример формата: "address=1234;type=1;flag=0;versionFW=2;...")
    QStringList pairs = data.split(';', Qt::SkipEmptyParts);

    for (const QString &pair : pairs) {
        QStringList keyValue = pair.split('=');
        if (keyValue.size() != 2) continue;

        QString key = keyValue[0].trimmed();
        QString value = keyValue[1].trimmed();

        if (key == "address") device.address = value;
        else if (key == "type") device.type = value;
        else if (key == "flag") device.flag = value;
        else if (key == "versionFW") device.versionFW = value;
        else if (key == "group_1") device.group_1 = value;
        else if (key == "group_2") device.group_2 = value;
        else if (key == "group_3") device.group_3 = value;
        else if (key == "group_4") device.group_4 = value;
        else if (key == "steps") device.steps = value;
        else if (key == "tiltAngle") device.tiltAngle = value;
        else if (key == "hight") device.hight = value;
        else if (key == "tiltOnly") device.tiltOnly = value;
        else if (key == "SAR") device.SAR = value;
        else if (key == "currentPosition") device.currentPosition = value;
        else if (key == "error") device.error = value;
        else if (key == "voltage") device.voltage = value;
        else if (key == "day") device.day = value;
        else if (key == "month") device.month = value;
        else if (key == "year") device.year = value;
        else if (key == "BR") device.BR = value;
        else if (key == "dir") device.dir = value;
    }

    return true;
}

bool ButtonHandler::parseSixChannelLine(const QString &line, SixChanel_t &device)
{
    // Убираем префикс "SIXCHANNEL:"
    QString data = line.mid(10); // Длина "SIXCHANNEL:"

    // Парсим данные
    QStringList pairs = data.split(';', Qt::SkipEmptyParts);

    for (const QString &pair : pairs) {
        QStringList keyValue = pair.split('=');
        if (keyValue.size() != 2) continue;

        QString key = keyValue[0].trimmed();
        QString value = keyValue[1].trimmed();

        if (key == "address") device.address = value;
        else if (key == "type") device.type = value;
        else if (key == "flag") device.flag = value;
        else if (key == "versionFW") device.versionFW = value;
        else if (key == "day") device.day = value;
        else if (key == "month") device.month = value;
        else if (key == "year") device.year = value;
        else if (key == "BR") device.BR = value;
        // Для каналов нужно добавить парсинг
        // Парсинг для канала 1
        else if (key == "ch1_address") device.chanel_1.address = value;
        else if (key == "ch1_chanel") device.chanel_1.chanel = value;
        else if (key == "ch1_group_1") device.chanel_1.group_1 = value;
        else if (key == "ch1_group_2") device.chanel_1.group_2 = value;
        else if (key == "ch1_group_3") device.chanel_1.group_3 = value;
        else if (key == "ch1_group_4") device.chanel_1.group_4 = value;
        else if (key == "ch1_steps") device.chanel_1.steps = value;
        else if (key == "ch1_endangle") device.chanel_1.endangle = value;
        else if (key == "ch1_hight") device.chanel_1.hight = value;
        else if (key == "ch1_tiltOnly") device.chanel_1.tiltOnly = value;
        else if (key == "ch1_SAR") device.chanel_1.SAR = value;
        else if (key == "ch1_currentPosition") device.chanel_1.currentPosition = value;
        else if (key == "ch1_error") device.chanel_1.error = value;
        else if (key == "ch1_dir") device.chanel_1.dir = value;

        // Парсинг для канала 2
        else if (key == "ch2_address") device.chanel_2.address = value;
        else if (key == "ch2_chanel") device.chanel_2.chanel = value;
        else if (key == "ch2_group_1") device.chanel_2.group_1 = value;
        else if (key == "ch2_group_2") device.chanel_2.group_2 = value;
        else if (key == "ch2_group_3") device.chanel_2.group_3 = value;
        else if (key == "ch2_group_4") device.chanel_2.group_4 = value;
        else if (key == "ch2_steps") device.chanel_2.steps = value;
        else if (key == "ch2_endangle") device.chanel_2.endangle = value;
        else if (key == "ch2_hight") device.chanel_2.hight = value;
        else if (key == "ch2_tiltOnly") device.chanel_2.tiltOnly = value;
        else if (key == "ch2_SAR") device.chanel_2.SAR = value;
        else if (key == "ch2_currentPosition") device.chanel_2.currentPosition = value;
        else if (key == "ch2_error") device.chanel_2.error = value;
        else if (key == "ch2_dir") device.chanel_2.dir = value;

        // Парсинг для канала 3
        else if (key == "ch3_address") device.chanel_3.address = value;
        else if (key == "ch3_chanel") device.chanel_3.chanel = value;
        else if (key == "ch3_group_1") device.chanel_3.group_1 = value;
        else if (key == "ch3_group_2") device.chanel_3.group_2 = value;
        else if (key == "ch3_group_3") device.chanel_3.group_3 = value;
        else if (key == "ch3_group_4") device.chanel_3.group_4 = value;
        else if (key == "ch3_steps") device.chanel_3.steps = value;
        else if (key == "ch3_endangle") device.chanel_3.endangle = value;
        else if (key == "ch3_hight") device.chanel_3.hight = value;
        else if (key == "ch3_tiltOnly") device.chanel_3.tiltOnly = value;
        else if (key == "ch3_SAR") device.chanel_3.SAR = value;
        else if (key == "ch3_currentPosition") device.chanel_3.currentPosition = value;
        else if (key == "ch3_error") device.chanel_3.error = value;
        else if (key == "ch3_dir") device.chanel_3.dir = value;

        // Парсинг для канала 4
        else if (key == "ch4_address") device.chanel_4.address = value;
        else if (key == "ch4_chanel") device.chanel_4.chanel = value;
        else if (key == "ch4_group_1") device.chanel_4.group_1 = value;
        else if (key == "ch4_group_2") device.chanel_4.group_2 = value;
        else if (key == "ch4_group_3") device.chanel_4.group_3 = value;
        else if (key == "ch4_group_4") device.chanel_4.group_4 = value;
        else if (key == "ch4_steps") device.chanel_4.steps = value;
        else if (key == "ch4_endangle") device.chanel_4.endangle = value;
        else if (key == "ch4_hight") device.chanel_4.hight = value;
        else if (key == "ch4_tiltOnly") device.chanel_4.tiltOnly = value;
        else if (key == "ch4_SAR") device.chanel_4.SAR = value;
        else if (key == "ch4_currentPosition") device.chanel_4.currentPosition = value;
        else if (key == "ch4_error") device.chanel_4.error = value;
        else if (key == "ch4_dir") device.chanel_4.dir = value;

        // Парсинг для канала 5
        else if (key == "ch5_address") device.chanel_5.address = value;
        else if (key == "ch5_chanel") device.chanel_5.chanel = value;
        else if (key == "ch5_group_1") device.chanel_5.group_1 = value;
        else if (key == "ch5_group_2") device.chanel_5.group_2 = value;
        else if (key == "ch5_group_3") device.chanel_5.group_3 = value;
        else if (key == "ch5_group_4") device.chanel_5.group_4 = value;
        else if (key == "ch5_steps") device.chanel_5.steps = value;
        else if (key == "ch5_endangle") device.chanel_5.endangle = value;
        else if (key == "ch5_hight") device.chanel_5.hight = value;
        else if (key == "ch5_tiltOnly") device.chanel_5.tiltOnly = value;
        else if (key == "ch5_SAR") device.chanel_5.SAR = value;
        else if (key == "ch5_currentPosition") device.chanel_5.currentPosition = value;
        else if (key == "ch5_error") device.chanel_5.error = value;
        else if (key == "ch5_dir") device.chanel_5.dir = value;

        // Парсинг для канала 6
        else if (key == "ch6_address") device.chanel_6.address = value;
        else if (key == "ch6_chanel") device.chanel_6.chanel = value;
        else if (key == "ch6_group_1") device.chanel_6.group_1 = value;
        else if (key == "ch6_group_2") device.chanel_6.group_2 = value;
        else if (key == "ch6_group_3") device.chanel_6.group_3 = value;
        else if (key == "ch6_group_4") device.chanel_6.group_4 = value;
        else if (key == "ch6_steps") device.chanel_6.steps = value;
        else if (key == "ch6_endangle") device.chanel_6.endangle = value;
        else if (key == "ch6_hight") device.chanel_6.hight = value;
        else if (key == "ch6_tiltOnly") device.chanel_6.tiltOnly = value;
        else if (key == "ch6_SAR") device.chanel_6.SAR = value;
        else if (key == "ch6_currentPosition") device.chanel_6.currentPosition = value;
        else if (key == "ch6_error") device.chanel_6.error = value;
        else if (key == "ch6_dir") device.chanel_6.dir = value;

    }

    return true;
}

/**/
void ButtonHandler::handleCopyButton(){
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
        QVector<OneChanel_t> devices = m_tableController->model()->getOneChanelData();//Полчили нужную строку

              oneChanelCopySetting.group_1   = devices[rowInfo.deviceIndex].group_1  ;
              oneChanelCopySetting.group_2   = devices[rowInfo.deviceIndex].group_2  ;
              oneChanelCopySetting.group_3   = devices[rowInfo.deviceIndex].group_3  ;
              oneChanelCopySetting.group_4   = devices[rowInfo.deviceIndex].group_4  ;
              oneChanelCopySetting.hight     = devices[rowInfo.deviceIndex].hight    ;
              oneChanelCopySetting.tiltAngle = devices[rowInfo.deviceIndex].tiltAngle;
              oneChanelCopySetting.tiltOnly  = devices[rowInfo.deviceIndex].tiltOnly ;
              oneChanelCopySetting.dir       = devices[rowInfo.deviceIndex].dir      ;
          //      m_tableController->model()->loadOneChanelData(devices);

    }
    else if (rowInfo.deviceType == TableModel::SixChannelDevice) {

        QVector<SixChanel_t> devices = m_tableController->model()->getSixChanelData();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
          sixChanelCopysSetting.chanel_1.group_1    = devices[rowInfo.deviceIndex].chanel_1.group_1    ;
          sixChanelCopysSetting.chanel_1.group_2    = devices[rowInfo.deviceIndex].chanel_1.group_2    ;
          sixChanelCopysSetting.chanel_1.group_3    = devices[rowInfo.deviceIndex].chanel_1.group_3    ;
          sixChanelCopysSetting.chanel_1.group_4    = devices[rowInfo.deviceIndex].chanel_1.group_4    ;
          sixChanelCopysSetting.chanel_1.hight      = devices[rowInfo.deviceIndex].chanel_1.hight      ;
          sixChanelCopysSetting.chanel_1.tiltAngle  = devices[rowInfo.deviceIndex].chanel_1.endangle   ;
          sixChanelCopysSetting.chanel_1.tiltOnly   = devices[rowInfo.deviceIndex].chanel_1.tiltOnly   ;
          sixChanelCopysSetting.chanel_1.dir        = devices[rowInfo.deviceIndex].chanel_1.dir        ;

          sixChanelCopysSetting.chanel_2.group_1    = devices[rowInfo.deviceIndex].chanel_2.group_1    ;
          sixChanelCopysSetting.chanel_2.group_2    = devices[rowInfo.deviceIndex].chanel_2.group_2    ;
          sixChanelCopysSetting.chanel_2.group_3    = devices[rowInfo.deviceIndex].chanel_2.group_3    ;
          sixChanelCopysSetting.chanel_2.group_4    = devices[rowInfo.deviceIndex].chanel_2.group_4    ;
          sixChanelCopysSetting.chanel_2.hight      = devices[rowInfo.deviceIndex].chanel_2.hight      ;
          sixChanelCopysSetting.chanel_2.tiltAngle  = devices[rowInfo.deviceIndex].chanel_2.endangle   ;
          sixChanelCopysSetting.chanel_2.tiltOnly   = devices[rowInfo.deviceIndex].chanel_2.tiltOnly   ;
          sixChanelCopysSetting.chanel_2.dir        = devices[rowInfo.deviceIndex].chanel_2.dir        ;

          sixChanelCopysSetting.chanel_3.group_1    = devices[rowInfo.deviceIndex].chanel_3.group_1    ;
          sixChanelCopysSetting.chanel_3.group_2    = devices[rowInfo.deviceIndex].chanel_3.group_2    ;
          sixChanelCopysSetting.chanel_3.group_3    = devices[rowInfo.deviceIndex].chanel_3.group_3    ;
          sixChanelCopysSetting.chanel_3.group_4    = devices[rowInfo.deviceIndex].chanel_3.group_4    ;
          sixChanelCopysSetting.chanel_3.hight      = devices[rowInfo.deviceIndex].chanel_3.hight      ;
          sixChanelCopysSetting.chanel_3.tiltAngle  = devices[rowInfo.deviceIndex].chanel_3.endangle   ;
          sixChanelCopysSetting.chanel_3.tiltOnly   = devices[rowInfo.deviceIndex].chanel_3.tiltOnly   ;
          sixChanelCopysSetting.chanel_3.dir        = devices[rowInfo.deviceIndex].chanel_3.dir        ;

          sixChanelCopysSetting.chanel_4.group_1    = devices[rowInfo.deviceIndex].chanel_4.group_1    ;
          sixChanelCopysSetting.chanel_4.group_2    = devices[rowInfo.deviceIndex].chanel_4.group_2    ;
          sixChanelCopysSetting.chanel_4.group_3    = devices[rowInfo.deviceIndex].chanel_4.group_3    ;
          sixChanelCopysSetting.chanel_4.group_4    = devices[rowInfo.deviceIndex].chanel_4.group_4    ;
          sixChanelCopysSetting.chanel_4.hight      = devices[rowInfo.deviceIndex].chanel_4.hight      ;
          sixChanelCopysSetting.chanel_4.tiltAngle  = devices[rowInfo.deviceIndex].chanel_4.endangle   ;
          sixChanelCopysSetting.chanel_4.tiltOnly   = devices[rowInfo.deviceIndex].chanel_4.tiltOnly   ;
          sixChanelCopysSetting.chanel_4.dir        = devices[rowInfo.deviceIndex].chanel_4.dir        ;

          sixChanelCopysSetting.chanel_5.group_1    = devices[rowInfo.deviceIndex].chanel_5.group_1    ;
          sixChanelCopysSetting.chanel_5.group_2    = devices[rowInfo.deviceIndex].chanel_5.group_2    ;
          sixChanelCopysSetting.chanel_5.group_3    = devices[rowInfo.deviceIndex].chanel_5.group_3    ;
          sixChanelCopysSetting.chanel_5.group_4    = devices[rowInfo.deviceIndex].chanel_5.group_4    ;
          sixChanelCopysSetting.chanel_5.hight      = devices[rowInfo.deviceIndex].chanel_5.hight      ;
          sixChanelCopysSetting.chanel_5.tiltAngle  = devices[rowInfo.deviceIndex].chanel_5.endangle   ;
          sixChanelCopysSetting.chanel_5.tiltOnly   = devices[rowInfo.deviceIndex].chanel_5.tiltOnly   ;
          sixChanelCopysSetting.chanel_5.dir        = devices[rowInfo.deviceIndex].chanel_5.dir        ;

          sixChanelCopysSetting.chanel_6.group_1    = devices[rowInfo.deviceIndex].chanel_6.group_1    ;
          sixChanelCopysSetting.chanel_6.group_2    = devices[rowInfo.deviceIndex].chanel_6.group_2    ;
          sixChanelCopysSetting.chanel_6.group_3    = devices[rowInfo.deviceIndex].chanel_6.group_3    ;
          sixChanelCopysSetting.chanel_6.group_4    = devices[rowInfo.deviceIndex].chanel_6.group_4    ;
          sixChanelCopysSetting.chanel_6.hight      = devices[rowInfo.deviceIndex].chanel_6.hight      ;
          sixChanelCopysSetting.chanel_6.tiltAngle  = devices[rowInfo.deviceIndex].chanel_6.endangle   ;
          sixChanelCopysSetting.chanel_6.tiltOnly   = devices[rowInfo.deviceIndex].chanel_6.tiltOnly   ;
          sixChanelCopysSetting.chanel_6.dir        = devices[rowInfo.deviceIndex].chanel_6.dir        ;
       }
    }
    else {
        qDebug() << "Неизвестный тип устройства";
        return;
    }


}

void ButtonHandler::handlePasteButton(){
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
        QVector<OneChanel_t> devices = m_tableController->model()->getOneChanelData();//Полчили нужную строку

        devices[rowInfo.deviceIndex].group_1    = oneChanelCopySetting.group_1    ;
        devices[rowInfo.deviceIndex].group_2    = oneChanelCopySetting.group_2    ;
        devices[rowInfo.deviceIndex].group_3    = oneChanelCopySetting.group_3    ;
        devices[rowInfo.deviceIndex].group_4    = oneChanelCopySetting.group_4    ;
        devices[rowInfo.deviceIndex].hight      = oneChanelCopySetting.hight      ;
        devices[rowInfo.deviceIndex].tiltAngle  = oneChanelCopySetting.tiltAngle  ;
        devices[rowInfo.deviceIndex].tiltOnly   = oneChanelCopySetting.tiltOnly   ;
        devices[rowInfo.deviceIndex].dir        = oneChanelCopySetting.dir        ;
        m_tableController->model()->loadOneChanelData(devices);

    }
    else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        // Обновление шестиканального устройства

        QVector<SixChanel_t> devices = m_tableController->model()->getSixChanelData();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные (только для первого канала)
            devices[rowInfo.deviceIndex].chanel_1.group_1   = sixChanelCopysSetting.chanel_1.group_1;
            devices[rowInfo.deviceIndex].chanel_1.group_2   = sixChanelCopysSetting.chanel_1.group_2;
            devices[rowInfo.deviceIndex].chanel_1.group_3   = sixChanelCopysSetting.chanel_1.group_3;
            devices[rowInfo.deviceIndex].chanel_1.group_4   = sixChanelCopysSetting.chanel_1.group_4;
            devices[rowInfo.deviceIndex].chanel_1.hight     = sixChanelCopysSetting.chanel_1.hight;
            devices[rowInfo.deviceIndex].chanel_1.endangle  = sixChanelCopysSetting.chanel_1.tiltAngle;
            devices[rowInfo.deviceIndex].chanel_1.tiltOnly  = sixChanelCopysSetting.chanel_1.tiltOnly;
            devices[rowInfo.deviceIndex].chanel_1.dir       = sixChanelCopysSetting.chanel_1.dir;

            devices[rowInfo.deviceIndex].chanel_2.group_1   = sixChanelCopysSetting.chanel_2.group_1;
            devices[rowInfo.deviceIndex].chanel_2.group_2   = sixChanelCopysSetting.chanel_2.group_2;
            devices[rowInfo.deviceIndex].chanel_2.group_3   = sixChanelCopysSetting.chanel_2.group_3;
            devices[rowInfo.deviceIndex].chanel_2.group_4   = sixChanelCopysSetting.chanel_2.group_4;
            devices[rowInfo.deviceIndex].chanel_2.hight     = sixChanelCopysSetting.chanel_2.hight;
            devices[rowInfo.deviceIndex].chanel_2.endangle  = sixChanelCopysSetting.chanel_2.tiltAngle;
            devices[rowInfo.deviceIndex].chanel_2.tiltOnly  = sixChanelCopysSetting.chanel_2.tiltOnly;
            devices[rowInfo.deviceIndex].chanel_2.dir       = sixChanelCopysSetting.chanel_2.dir;

            devices[rowInfo.deviceIndex].chanel_3.group_1   = sixChanelCopysSetting.chanel_3.group_1;
            devices[rowInfo.deviceIndex].chanel_3.group_2   = sixChanelCopysSetting.chanel_3.group_2;
            devices[rowInfo.deviceIndex].chanel_3.group_3   = sixChanelCopysSetting.chanel_3.group_3;
            devices[rowInfo.deviceIndex].chanel_3.group_4   = sixChanelCopysSetting.chanel_3.group_4;
            devices[rowInfo.deviceIndex].chanel_3.hight     = sixChanelCopysSetting.chanel_3.hight;
            devices[rowInfo.deviceIndex].chanel_3.endangle  = sixChanelCopysSetting.chanel_3.tiltAngle;
            devices[rowInfo.deviceIndex].chanel_3.tiltOnly  = sixChanelCopysSetting.chanel_3.tiltOnly;
            devices[rowInfo.deviceIndex].chanel_3.dir       = sixChanelCopysSetting.chanel_3.dir;

            devices[rowInfo.deviceIndex].chanel_4.group_1   = sixChanelCopysSetting.chanel_4.group_1;
            devices[rowInfo.deviceIndex].chanel_4.group_2   = sixChanelCopysSetting.chanel_4.group_2;
            devices[rowInfo.deviceIndex].chanel_4.group_3   = sixChanelCopysSetting.chanel_4.group_3;
            devices[rowInfo.deviceIndex].chanel_4.group_4   = sixChanelCopysSetting.chanel_4.group_4;
            devices[rowInfo.deviceIndex].chanel_4.hight     = sixChanelCopysSetting.chanel_4.hight;
            devices[rowInfo.deviceIndex].chanel_4.endangle  = sixChanelCopysSetting.chanel_4.tiltAngle;
            devices[rowInfo.deviceIndex].chanel_4.tiltOnly  = sixChanelCopysSetting.chanel_4.tiltOnly;
            devices[rowInfo.deviceIndex].chanel_4.dir       = sixChanelCopysSetting.chanel_4.dir;

            devices[rowInfo.deviceIndex].chanel_5.group_1   = sixChanelCopysSetting.chanel_5.group_1;
            devices[rowInfo.deviceIndex].chanel_5.group_2   = sixChanelCopysSetting.chanel_5.group_2;
            devices[rowInfo.deviceIndex].chanel_5.group_3   = sixChanelCopysSetting.chanel_5.group_3;
            devices[rowInfo.deviceIndex].chanel_5.group_4   = sixChanelCopysSetting.chanel_5.group_4;
            devices[rowInfo.deviceIndex].chanel_5.hight     = sixChanelCopysSetting.chanel_5.hight;
            devices[rowInfo.deviceIndex].chanel_5.endangle  = sixChanelCopysSetting.chanel_5.tiltAngle;
            devices[rowInfo.deviceIndex].chanel_5.tiltOnly  = sixChanelCopysSetting.chanel_5.tiltOnly;
            devices[rowInfo.deviceIndex].chanel_5.dir       = sixChanelCopysSetting.chanel_5.dir;

            devices[rowInfo.deviceIndex].chanel_6.group_1   = sixChanelCopysSetting.chanel_6.group_1;
            devices[rowInfo.deviceIndex].chanel_6.group_2   = sixChanelCopysSetting.chanel_6.group_2;
            devices[rowInfo.deviceIndex].chanel_6.group_3   = sixChanelCopysSetting.chanel_6.group_3;
            devices[rowInfo.deviceIndex].chanel_6.group_4   = sixChanelCopysSetting.chanel_6.group_4;
            devices[rowInfo.deviceIndex].chanel_6.hight     = sixChanelCopysSetting.chanel_6.hight;
            devices[rowInfo.deviceIndex].chanel_6.endangle  = sixChanelCopysSetting.chanel_6.tiltAngle;
            devices[rowInfo.deviceIndex].chanel_6.tiltOnly  = sixChanelCopysSetting.chanel_6.tiltOnly;
            devices[rowInfo.deviceIndex].chanel_6.dir       = sixChanelCopysSetting.chanel_6.dir;


                // Здесь нужно добавить метод в DataParser для обновления шестиканальных устройств
            m_tableController->model()->loadSixChanelData(devices);
        }
    }
    else {
        qDebug() << "Неизвестный тип устройства";
        return;
    }


}

/************************* Управление жалюзи *****************************/
/*
Подъем
*/
void ButtonHandler::handlebuttonsBlindsControlbutton_UP(){
QByteArray cmd;
    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {//Для одноканального контроллера
        QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
        if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
            return ;
        }
        const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];//Получаем данные из выбранной строки
        cmd.append(">");
        cmd.append(device.address);
        cmd.append("ru");
        cmd.append("1");//Для одноканальног8о контроллера канал всегда - 1
        cmd.append("<");
    }
    else if(rowInfo.deviceType == TableModel::SixChannelDevice){
        // Для шестиканального устройства channelIndex указывает на канал (0-5)
         int channelIndex = rowInfo.channelIndex;
         int deviceIndex = rowInfo.deviceIndex;

         qDebug() << "Выбран канал" << (channelIndex + 1) << "шестиканального устройства с индексом" << deviceIndex;
         cmd.append(">");
         cmd.append(QString("%1").arg(deviceIndex, 4, 10, QChar('0')).toUtf8());
         cmd.append("ru");
         cmd.append(QString::number(channelIndex + 1));
         cmd.append("<");


         {
//         // Получаем данные устройства
//         QVector<SixChanel_t> sixChannelData = m_tableController->model()->getSixChanelData();
//         if (deviceIndex >= 0 && deviceIndex < sixChannelData.size()) {
//             const SixChanel_t &device = sixChannelData[deviceIndex];

//             // Получаем данные конкретного канала
//             const Chanel_t* selectedChannel = nullptr;
//             switch (channelIndex) {
//                 case 0: selectedChannel = &device.chanel_1; break;
//                 case 1: selectedChannel = &device.chanel_2; break;
//                 case 2: selectedChannel = &device.chanel_3; break;
//                 case 3: selectedChannel = &device.chanel_4; break;
//                 case 4: selectedChannel = &device.chanel_5; break;
//                 case 5: selectedChannel = &device.chanel_6; break;
//             }

//             if (selectedChannel) {
//                 qDebug() << "Данные канала:"
//                          << "Группы:" << selectedChannel->group_1 << selectedChannel->group_2
//                          << selectedChannel->group_3 << selectedChannel->group_4
//                          << "Высота:" << selectedChannel->hight
//                          << "Угол:" << selectedChannel->endangle;
//             }
//         }
         }

    }



emit signalSendData(cmd);

}

/*
Кратковременный подьем
*/
void ButtonHandler::handlebuttonsBlindsControlbutton_UpLeft(){
QByteArray cmd;
    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {//Для одноканального контроллера
        QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
        if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
            return ;
        }
        const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];//Получаем данные из выбранной строки
        cmd.append(">");
        cmd.append(device.address);
        cmd.append("tu");
        cmd.append("1");//Для одноканального контроллера канал всегда - 1
        cmd.append("<");
    }
    else if(rowInfo.deviceType == TableModel::SixChannelDevice){
        // Для шестиканального устройства channelIndex указывает на канал (0-5)
         int channelIndex = rowInfo.channelIndex;
         int deviceIndex = rowInfo.deviceIndex;

         qDebug() << "Выбран канал" << (channelIndex + 1) << "шестиканального устройства с индексом" << deviceIndex;
         cmd.append(">");
         cmd.append(QString("%1").arg(deviceIndex, 4, 10, QChar('0')).toUtf8());
         cmd.append("tu");
         cmd.append(QString::number(channelIndex + 1));
         cmd.append("<");
    }

emit signalSendData(cmd);
}

/*
Спуск
*/
void ButtonHandler::handlebuttonsBlindsControlbutton_Down(){
QByteArray cmd;
    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {//Для одноканального контроллера
        QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
        if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
            return ;
        }
        const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];//Получаем данные из выбранной строки
        cmd.append(">");
        cmd.append(device.address);
        cmd.append("rd");
        cmd.append("1");//Для одноканального контроллера канал всегда - 1
        cmd.append("<");
    }
    else if(rowInfo.deviceType == TableModel::SixChannelDevice){
        // Для шестиканального устройства channelIndex указывает на канал (0-5)
         int channelIndex = rowInfo.channelIndex;
         int deviceIndex = rowInfo.deviceIndex;

         qDebug() << "Выбран канал" << (channelIndex + 1) << "шестиканального устройства с индексом" << deviceIndex;
         cmd.append(">");
         cmd.append(QString("%1").arg(deviceIndex, 4, 10, QChar('0')).toUtf8());
         cmd.append("rd");
         cmd.append(QString::number(channelIndex + 1));
         cmd.append("<");
    }

emit signalSendData(cmd);
}

/*
Кратковременный спуск
*/
void ButtonHandler::handlebuttonsBlindsControlbutton_DownRight(){
QByteArray cmd;
    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {//Для одноканального контроллера
        QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
        if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
            return ;
        }
        const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];//Получаем данные из выбранной строки
        cmd.append(">");
        cmd.append(device.address);
        cmd.append("td");
        cmd.append("1");//Для одноканального контроллера канал всегда - 1
        cmd.append("<");
    }
    else if(rowInfo.deviceType == TableModel::SixChannelDevice){
        // Для шестиканального устройства channelIndex указывает на канал (0-5)
         int channelIndex = rowInfo.channelIndex;
         int deviceIndex = rowInfo.deviceIndex;

         qDebug() << "Выбран канал" << (channelIndex + 1) << "шестиканального устройства с индексом" << deviceIndex;
         cmd.append(">");
         cmd.append(QString("%1").arg(deviceIndex, 4, 10, QChar('0')).toUtf8());
         cmd.append("td");
         cmd.append(QString::number(channelIndex + 1));
         cmd.append("<");
    }

emit signalSendData(cmd);
}
/*
Стоп
*/
void ButtonHandler::handlebuttonsBlindsControlbutton_Stop(){
QByteArray cmd;
    int selectedRow = m_tableController->selectedRow();//Получаем номер выбранной строки
    TableModel::TableRowInfo rowInfo = m_tableController->model()->getRowInfo(selectedRow);


    if (rowInfo.deviceType == TableModel::OneChannelDevice) {//Для одноканального контроллера
        QVector<OneChanel_t> oneChannelData = m_tableController->model()->getOneChanelData();
        if (rowInfo.deviceIndex < 0 || rowInfo.deviceIndex >= oneChannelData.size()) {
            return ;
        }
        const OneChanel_t &device = oneChannelData[rowInfo.deviceIndex];//Получаем данные из выбранной строки
        cmd.append(">");
        cmd.append(device.address);
        cmd.append("gs");
        cmd.append("1");//Для одноканального контроллера канал всегда - 1
        cmd.append("<");
    }
    else if(rowInfo.deviceType == TableModel::SixChannelDevice){
        // Для шестиканального устройства channelIndex указывает на канал (0-5)
         int channelIndex = rowInfo.channelIndex;
         int deviceIndex = rowInfo.deviceIndex;

         qDebug() << "Выбран канал" << (channelIndex + 1) << "шестиканального устройства с индексом" << deviceIndex;
         cmd.append(">");
         cmd.append(QString("%1").arg(deviceIndex, 4, 10, QChar('0')).toUtf8());
         cmd.append("gs");
         cmd.append(QString::number(channelIndex + 1));
         cmd.append("<");
    }

emit signalSendData(cmd);
}

/******************* Управление всеми каналами ********************/

/*
Подъем
*/
void ButtonHandler::handlebuttonsBlindsControlAllbutton_UP(){
QByteArray cmd;
        cmd.append(">");
        cmd.append("****");
        cmd.append("ru");
        cmd.append("<");

emit signalSendData(cmd);

}

/*
Кратковременный подьем
*/
void ButtonHandler::handlebuttonsBlindsControlAllbutton_UpLeft(){
QByteArray cmd;

        cmd.append(">");
        cmd.append("****");
        cmd.append("tu");
        cmd.append("<");



emit signalSendData(cmd);
}

/*
Спуск
*/
void ButtonHandler::handlebuttonsBlindsControlAllbutton_Down(){
QByteArray cmd;
        cmd.append(">");
        cmd.append("****");
        cmd.append("rd");
        cmd.append("<");
emit signalSendData(cmd);
}

/*
Кратковременный спуск
*/
void ButtonHandler::handlebuttonsBlindsControlAllbutton_DownRight(){
QByteArray cmd;
        cmd.append(">");
        cmd.append("****");
        cmd.append("td");
        cmd.append("<");

emit signalSendData(cmd);
}
/*
Стоп
*/
void ButtonHandler::handlebuttonsBlindsControlAllbutton_Stop(){
QByteArray cmd;

        cmd.append(">");
        cmd.append("****");
        cmd.append("gs");
        cmd.append("<");

    emit signalSendData(cmd);
}
