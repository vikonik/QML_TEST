// TableController.cpp
#include "tablecontroller.h"
#include "tablemodel.h"
#include <QDebug>

TableController::TableController(QObject *parent)
    : QObject(parent), m_model(nullptr), m_dataParser(nullptr), m_selectedRow(-1)
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

    // Сохраняем выбранную строку
    setSelectedRow(rowIndex);

    // Получаем полные данные из DataParser
    QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();

    if (rowIndex < 0 || rowIndex >= devices.size()) {
        qWarning() << "Invalid row index:" << rowIndex;
        return;
    }

    const OneChanel_t &device = devices[rowIndex];

    // Извлекаем нужные данные
    m_serialText = device.address;
    m_minAngleText = device.tiltAngle;
    m_typeText = device.versionFW;

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
    qDebug()<<"processRow complite" << m_serialText << "row index:" << rowIndex;
}

/*
Обновляем таблицу при изменении serialID
*/
void TableController::updateSerialValue(const QString &newValue)
{
    if (!m_model || m_selectedRow < 0 || !m_dataParser) {
           qWarning() << "Cannot update serial value: model not set, no row selected, or data parser not set";
           return;
       }

    // Получаем текущие данные
        QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();

    if (m_selectedRow < 0) {
        qWarning() << "Cannot update serial value: no row selected";
        return;
    }

    if (m_selectedRow < devices.size()) {
        // Обновляем исходные данные
        devices[m_selectedRow].address = newValue;
        // Здесь нужно добавить метод в DataParser для обновления устройств,
        m_dataParser->setOneChanelDevices(devices);
    }

    // Обновляем значение в модели
    m_model->updateCell(m_selectedRow, 0, newValue);

    // Также обновляем наше свойство для PanelInfo
    m_serialText = newValue;
    emit dataProcessed();

    qDebug() << "Updated serial value to:" << newValue << "for row:" << m_selectedRow << "m_serialText " << m_serialText;
}

/**/
int TableController::selectedRow() const
{
    return m_selectedRow;
}

void TableController::setSelectedRow(int row)
{
    if (m_selectedRow != row) {
        m_selectedRow = row;
        emit selectedRowChanged();
    }
}
// Реализация геттеров
QString TableController::serialText() const {
     qDebug() << "serialText m_serialText " << m_serialText;
    return m_serialText;
}
QString TableController::minAngleText() const { return m_minAngleText; }
QString TableController::typeText() const { return m_typeText; }
QString TableController::activationDateText() const { return m_activationDateText; }
