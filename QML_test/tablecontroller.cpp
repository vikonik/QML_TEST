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
            //m_typeText = device.versionFW;
            if(device.type == "A")
                m_typeText = "1-CH";
            else
                m_typeText = "Unknown";
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
          //  m_typeText = device.versionFW;
            if(device.type == "B")
                m_typeText = "6-CH";
            else
                m_typeText = "Unknown";
            // Форматирование даты
            QString formattedDay = device.day.length() == 1 ? "0" + device.day : device.day;
            QString formattedMonth = device.month.length() == 1 ? "0" + device.month : device.month;
            QString formattedYear = device.year.right(2);

            m_activationDateText = QString("%1.%2.%3")
                .arg(formattedDay)
                .arg(formattedMonth)
                .arg(formattedYear);

            // Для многоканальных устройств minAngle может быть не применим
           // m_minAngleText = "N/A";


                    switch ( rowInfo.channelIndex) {
                        case 0: m_minAngleText =  device.chanel_1.endangle;break;
                        case 1: m_minAngleText =  device.chanel_2.endangle;break;
                        case 2: m_minAngleText =  device.chanel_3.endangle;break;
                        case 3: m_minAngleText =  device.chanel_4.endangle;break;
                        case 4: m_minAngleText =  device.chanel_5.endangle;break;
                        case 5: m_minAngleText =  device.chanel_6.endangle;break;
                        default: m_minAngleText = "N/A";break;
                    }

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

/*
Обновляем таблицу при изменении serialID
*/
void TableController::updateSerialValue(const QString &newValue)
{
    if (!m_model || m_selectedRow < 0 || !m_dataParser) {
           qWarning() << "Cannot update serial value: model not set, no row selected, or data parser not set";
           return;
       }

    // Получаем информацию о типе строки
    TableModel::TableRowInfo rowInfo = m_model->getRowInfo(m_selectedRow);

    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        // Обновление одноканального устройства
        QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные
            devices[rowInfo.deviceIndex].address = newValue;
            m_dataParser->setOneChanelDevices(devices);
        }
    } else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        // Обновление шестиканального устройства
        QVector<SixChanel_t> devices = m_dataParser->getSixChanelDevices();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные (только для первого канала)
            devices[rowInfo.deviceIndex].address = newValue;
            // Здесь нужно добавить метод в DataParser для обновления шестиканальных устройств
            // m_dataParser->setSixChanelDevices(devices);
        }
    }

    // Обновляем значение в модели
    m_model->updateCell(m_selectedRow, 0, newValue);

    // Также обновляем наше свойство для PanelInfo
    m_serialText = newValue;
    emit dataProcessed();

    m_model->resortTable();


    qDebug() << "Updated serial value to:" << newValue << "for row:" << m_selectedRow << "m_serialText " << m_serialText;
}

/**/
int TableController::selectedRow() const
{
    return m_selectedRow;
}

void TableController::setSelectedRow(int row)
{
    qDebug() << "Выбрана строка";
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

// Вспомогательный метод для сброса значений отображения
void TableController::resetDisplayValues()
{
    m_serialText = "";
    m_minAngleText = "";
    m_typeText = "";
    m_activationDateText = "";
}

/**/
void TableController::updateCellsInRange(int startRow, int startCol, int endRow, int endCol, const QString &value)
{
    if (!m_model) return;

    int minRow = qMin(startRow, endRow);
    int maxRow = qMax(startRow, endRow);
    int minCol = qMin(startCol, endCol);
    int maxCol = qMax(startCol, endCol);

    for (int row = minRow; row <= maxRow; ++row) {
        for (int col = minCol; col <= maxCol; ++col) {
            if (col >= 5 && col <= 8) { // Только столбцы 5-8
                m_model->updateCell(row, col, value);
            }
        }
    }
}

/**/
QString TableController::getSerialIDForRow(int row) const
{
    if (!m_model || row < 0) {
        return QString();
    }

    TableModel::TableRowInfo rowInfo = m_model->getRowInfo(row);

    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        return getSerialFromOneChannel(rowInfo.deviceIndex);
    } else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        return getSerialFromSixChannel(rowInfo.deviceIndex);
    }

    return QString();
}

QString TableController::getSerialFromOneChannel(int deviceIndex) const
{
    if (!m_dataParser || deviceIndex < 0) {
        return QString();
    }

    QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();
    if (deviceIndex >= 0 && deviceIndex < devices.size()) {
        return devices[deviceIndex].address;
    }

    return QString();
}

QString TableController::getSerialFromSixChannel(int deviceIndex) const
{
    if (!m_dataParser || deviceIndex < 0) {
        return QString();
    }

    QVector<SixChanel_t> devices = m_dataParser->getSixChanelDevices();
    if (deviceIndex >= 0 && deviceIndex < devices.size()) {
        return devices[deviceIndex].address;
    }

    return QString();
}

/*
Устанаваливаем настройки поумолчанию для выбранной строки
*/
void TableController::defaultSetupSelectedRow(){
    if (!m_model || m_selectedRow < 0 || !m_dataParser) {
           qWarning() << "Cannot update serial value: model not set, no row selected, or data parser not set";
           return;
       }

    // Получаем информацию о типе строки
    TableModel::TableRowInfo rowInfo = m_model->getRowInfo(m_selectedRow);

    if (rowInfo.deviceType == TableModel::OneChannelDevice) {
        // Обновление одноканального устройства
        QVector<OneChanel_t> devices = m_dataParser->getOneChanelDevices();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные
            //devices[rowInfo.deviceIndex].address = newValue;
            devices[rowInfo.deviceIndex].group_1 = "9999";



            m_dataParser->setOneChanelDevices(devices);
        }
    } else if (rowInfo.deviceType == TableModel::SixChannelDevice) {
        // Обновление шестиканального устройства
        QVector<SixChanel_t> devices = m_dataParser->getSixChanelDevices();

        if (rowInfo.deviceIndex >= 0 && rowInfo.deviceIndex < devices.size()) {
            // Обновляем исходные данные (только для первого канала)
            //!!!devices[rowInfo.deviceIndex].address = newValue;

            // Здесь нужно добавить метод в DataParser для обновления шестиканальных устройств
            // m_dataParser->setSixChanelDevices(devices);
        }
    }

    // Обновляем значение в модели
//    m_model->updateCell(m_selectedRow, 0, newValue);

//    // Также обновляем наше свойство для PanelInfo
//    m_serialText = newValue;
    emit dataProcessed();

    m_model->resortTable();


//    qDebug() << "Updated serial value to:" << newValue << "for row:" << m_selectedRow << "m_serialText " << m_serialText;

}
