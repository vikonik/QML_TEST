// TableController.cpp
#include "tablecontroller.h"
#include "tablemodel.h"
#include <QDebug>

TableController::TableController(QObject *parent)
    : QObject(parent), m_model(nullptr)
{
}

void TableController::setModel(TableModel *model)
{
    if (m_model != model) {
        m_model = model;
    }
}

void TableController::setDataParser(DataParser *dataParser)
{
    m_dataParser = dataParser;
}

void TableController::processRow(int rowIndex)
{
    if (!m_dataParser) {
         qWarning() << "DataParser is not set!";
         return;
     }

     // Получаем полные данные из DataParser
     QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();

     // Получаем полные данные из модели
    // QVector<OneChanel_t> devices = m_model->getFullData();


     if (rowIndex < 0 || rowIndex >= devices.size()) {
         qWarning() << "Invalid row index:" << rowIndex;
         return;
     }

     const OneChanel_t &device = devices[rowIndex];

     // Извлекаем нужные данные
     m_serialText = device.address;
     m_minAngleText = device.tiltAngle;
     m_typeText = "1-Ch";

     // Форматируем дату
     QString formattedDay = device.day.length() == 1 ? "0" + device.day : device.day;
     QString formattedMonth = device.month.length() == 1 ? "0" + device.month : device.month;

     // Берем последние две цифры года
     QString formattedYear = device.year;
     if (device.year.length() >= 2) {
         formattedYear = device.year.right(2);
     } else if (device.year.length() == 1) {
         formattedYear = "0" + device.year;
     }

     // Собираем итоговую строку даты
     m_activationDateText = QString("%1.%2.%3")
         .arg(formattedDay)
         .arg(formattedMonth)
         .arg(formattedYear);

     // Уведомляем об изменении данных
     emit dataProcessed();
}


// Реализация геттеров
QString TableController::serialText() const { return m_serialText; }
QString TableController::minAngleText() const { return m_minAngleText; }
QString TableController::typeText() const { return m_typeText; }
QString TableController::activationDateText() const { return m_activationDateText; }
