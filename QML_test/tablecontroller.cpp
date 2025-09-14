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
    if (!m_dataParser || !m_model) {
        qWarning() << "DataParser or Model is not set!";
        return;
    }

    // Сохраняем выбранную строку
    setSelectedRow(rowIndex);

    // Получаем информацию о типе строки из модели
    TableModel::TableRowInfo rowInfo = m_model->getRowInfo(rowIndex);

    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        // Обработка одноканального устройства
        QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            const OneChanel_t &device = devices[rowInfo.deviceIndex];

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
        } else {
            qWarning() << "Invalid device index for OneChannelDevice:" << rowInfo.deviceIndex;
            resetDisplayValues();
        }
    } else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        // Обработка многоканального устройства
        QVector<SixChanel_t> devices = m_dataParser->getSixChanelDevices();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            const SixChanel_t &device = devices[rowInfo.deviceIndex];

            // Заполняем данные устройства
            m_serialText = device.address;
            m_typeText = device.versionFW;

            // Форматирование даты
            QString formattedDay = device.day.length() == 1 ? "0" + device.day : device.day;
            QString formattedMonth = device.month.length() == 1 ? "0" + device.month : device.month;
            QString formattedYear = device.year.right(2);

            m_activationDateText = QString("%1.%2.%3")
                .arg(formattedDay)
                .arg(formattedMonth)
                .arg(formattedYear);

            // Для многоканальных устройств minAngle может быть не применим
            // Можно использовать значение из первого канала или оставить N/A
            m_minAngleText = "N/A";

            // Если нужно использовать значение из конкретного канала:
            /*
            if (rowInfo.channelIndex >= 0 && rowInfo.channelIndex < 6) {
                const Chanel_t* channel = nullptr;
                switch (rowInfo.channelIndex) {
                    case 0: channel = &device.chanel_1; break;
                    case 1: channel = &device.chanel_2; break;
                    case 2: channel = &device.chanel_3; break;
                    case 3: channel = &device.chanel_4; break;
                    case 4: channel = &device.chanel_5; break;
                    case 5: channel = &device.chanel_6; break;
                }

                if (channel) {
                    m_minAngleText = channel->endangle;
                }
            }
            */
        } else {
            qWarning() << "Invalid device index for SixChannelDevice:" << rowInfo.deviceIndex;
            resetDisplayValues();
        }
    } else {
        qWarning() << "Unknown device type for row:" << rowIndex;
        resetDisplayValues();
    }

    // Уведомляем об изменении данных
    emit dataProcessed();
    qDebug() << "processRow complete" << m_serialText << "row index:" << rowIndex;
}

// Вспомогательный метод для сброса значений отображения
void TableController::resetDisplayValues()
{
    m_serialText = "";
    m_minAngleText = "";
    m_typeText = "";
    m_activationDateText = "";
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
