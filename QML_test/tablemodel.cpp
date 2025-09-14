#include "tablemodel.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "dataStruct.h"

TableModel::TableModel(QObject *parent) : QAbstractListModel(parent) {}

int TableModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_data.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    if (role == RowDataRole)
        return QVariant::fromValue(m_data[index.row()]);

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != RowDataRole)
        return false;

    if (index.row() < 0 || index.row() >= m_data.size())
        return false;

    // Для упрощения будем считать, что value - это вся строка
    if (value.canConvert<QList<QVariant>>()) {
        m_data[index.row()] = value.value<QList<QVariant>>();
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
}

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RowDataRole] = "rowData";
    return roles;
}

void TableModel::addRow(const QList<QVariant> &row) {
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(row);
    endInsertRows();
}

void TableModel::setModelData(const QList<QList<QVariant>> &newData) {
    beginResetModel();
    m_data = newData;
    endResetModel();
}

void TableModel::loadCSV(const QString &filePath) {
    beginResetModel();
    m_data.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file:" << filePath;
        endResetModel();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QList<QVariant> row;
        QStringList fields = line.split(',');

        for (QString field : fields) {
            // Удаление кавычек если есть
            if (field.startsWith('"') && field.endsWith('"')) {
                field = field.mid(1, field.length() - 2);
            }
            row.append(field);
        }

        m_data.append(row);
    }

    file.close();
    endResetModel();
    qDebug() << "Loaded" << m_data.size() << "rows from" << filePath;
}

/*
Получаем данные из DataParser для одноканальных устройств
*/
void TableModel::loadOneChanelData(const QVector<OneChanel_t>& data){
    beginResetModel();
    m_oneChanelData = data;
    m_sixChanelData.clear();
    rebuildTableData();
    endResetModel();
}

/*
Получаем данные из DataParser для шестиканальных устройств
*/
void TableModel::loadSixChanelData(const QVector<SixChanel_t>& data){
    beginResetModel();
    m_sixChanelData = data;
    m_oneChanelData.clear();
    rebuildTableData();
    endResetModel();
}

/*
Добавляем одноканальное устройство
*/
void TableModel::addOneChanelDevice(const OneChanel_t &device) {
    // Поиск существующего устройства по адресу
    bool found = false;
    for (int i = 0; i < m_oneChanelData.size(); ++i) {
        if (m_oneChanelData[i].address == device.address) {
            m_oneChanelData[i] = device;
            found = true;
            break;
        }
    }

    // Если устройство не найдено, добавляем его
    if (!found) {
        m_oneChanelData.append(device);
    }

    // Перестраиваем таблицу
    rebuildTableData();
}

/*
Добавляем шестиканальное устройство
*/
void TableModel::addSixChanelDevice(const SixChanel_t &device) {
    // Поиск существующего устройства по адресу
    bool found = false;
    for (int i = 0; i < m_sixChanelData.size(); ++i) {
        if (m_sixChanelData[i].address == device.address) {
            m_sixChanelData[i] = device;
            found = true;
            break;
        }
    }

    // Если устройство не найдено, добавляем его
    if (!found) {
        m_sixChanelData.append(device);
    }

    // Перестраиваем таблицу
    rebuildTableData();
}

/*
Перестраиваем табличные данные на основе сохраненных устройств
*/
void TableModel::rebuildTableData() {
    beginResetModel();
    m_data.clear();
    m_rowInfo.clear();

    // Добавляем одноканальные устройства
    for (int i = 0; i < m_oneChanelData.size(); ++i) {
        const OneChanel_t &device = m_oneChanelData[i];
        QList<QVariant> row;

        row.append(device.address);    // Serial ID
        row.append("Device");          // Device
        row.append(device.versionFW);  // FW
        row.append("1");               // Channel
        row.append(device.error);      // Error
        row.append(device.group_1);    // Group 1
        row.append(device.group_2);    // Group 2
        row.append(device.group_3);    // Group 3
        row.append(device.group_4);    // Group 4
        row.append(device.hight);      // Height
        row.append(device.tiltAngle);  // End Angle
        row.append(device.tiltOnly);   // Tilt only
        row.append(device.dir);        // Motor revers

        m_data.append(row);

        TableRowInfo info;
        info.deviceType = OneChannelDevice;
        info.deviceIndex = i;
        info.channelIndex = 0;
        m_rowInfo.append(info);
    }

    // Добавляем шестиканальные устройства
    for (int i = 0; i < m_sixChanelData.size(); ++i) {
        const SixChanel_t &device = m_sixChanelData[i];

        // Массив каналов для удобного доступа
        const Chanel_t* channels[6] = {
            &device.chanel_1, &device.chanel_2, &device.chanel_3,
            &device.chanel_4, &device.chanel_5, &device.chanel_6
        };

        // Для каждого канала создаем отдельную строку
        for (int channelIdx = 0; channelIdx < 6; ++channelIdx) {
            const Chanel_t* channel = channels[channelIdx];
            QList<QVariant> row;

            // Заполняем общие данные только для первого канала
            if (channelIdx == 0) {
                row.append(device.address);    // Serial ID
                row.append("Device");          // Device
                row.append(device.versionFW);  // FW
            } else {
                row.append(""); // Пустое поле Serial ID
                row.append(""); // Пустое поле Device
                row.append(""); // Пустое поле FW
            }

            row.append(channel->chanel);       // Channel
            row.append(channel->error);        // Error
            row.append(channel->group_1);      // Group 1
            row.append(channel->group_2);      // Group 2
            row.append(channel->group_3);      // Group 3
            row.append(channel->group_4);      // Group 4
            row.append(channel->hight);        // Height
            row.append(channel->endangle);     // End Angle
            row.append(channel->tiltOnly);     // Tilt only
            row.append(channel->dir);          // Motor revers

            m_data.append(row);

            TableRowInfo info;
            info.deviceType = SixChannelDevice;
            info.deviceIndex = i;
            info.channelIndex = channelIdx;
            m_rowInfo.append(info);
        }
    }

    endResetModel();
    qDebug() << "Rebuilt table with" << m_data.size() << "rows";
}

/*
Получаем информацию о строке
*/
TableModel::TableRowInfo TableModel::getRowInfo(int row) const {
    if (row >= 0 && row < m_rowInfo.size()) {
        return m_rowInfo[row];
    }

    TableRowInfo info;
    info.deviceType = OneChannelDevice;
    info.deviceIndex = -1;
    info.channelIndex = -1;
    return info;
}

/**/
// Добавляем метод для получения полных данных одноканальных устройств
QVector<OneChanel_t> TableModel::getOneChanelData() const {
    return m_oneChanelData;
}

// Добавляем метод для получения полных данных шестиканальных устройств
QVector<SixChanel_t> TableModel::getSixChanelData() const {
    return m_sixChanelData;
}

/**/
void TableModel::clear() {
    beginResetModel();
    m_data.clear();
    m_oneChanelData.clear();
    m_sixChanelData.clear();
    m_rowInfo.clear();
    endResetModel();
}

// Установка редактируемых столбцов
QVariantList TableModel::editableColumns() const {
    QVariantList list;
    for (int col : m_editableColumns) {
        list.append(col);
    }
    return list;
}

void TableModel::setEditableColumns(const QVariantList &columns) {
    m_editableColumns.clear();
    for (const QVariant &col : columns) {
        if (col.isValid() && col.canConvert<int>()) {
            m_editableColumns.append(col.toInt());
        }
    }
    emit editableColumnsChanged();
}

// Проверка возможности редактирования ячейки
bool TableModel::isCellEditable(int row, int column) const {
    // Первая строка (заголовки) не редактируется
    if (row == 0) return false;

    return (m_editableColumns.contains(column) || column == 0) &&
           row >= 0 && row < m_data.size() &&
           column >= 0 && column < m_data[row].size();
}

// Обновление значения ячейки
void TableModel::updateCell(int row, int column, const QVariant &value) {
    qDebug() << "Updating cell - Row:" << row << "Column:" << column << "Value:" << value;

    if (row < 0 || row >= m_data.size() ||
        column < 0 || column >= m_data[row].size()) {
        qWarning() << "Invalid cell:" << row << column;
        return;
    }

    if (!isCellEditable(row, column)) {
        qWarning() << "Cell not editable:" << row << column;
        return;
    }

    // Обновляем значение
    m_data[row][column] = value;

    // Обновляем исходные данные
    TableRowInfo info = getRowInfo(row);
    if (info.deviceType == OneChannelDevice && info.deviceIndex >= 0 && info.deviceIndex < m_oneChanelData.size()) {
        OneChanel_t &device = m_oneChanelData[info.deviceIndex];
        // Обновляем соответствующее поле устройства
        switch (column) {
            case 0: device.address = value.toString(); break;
            case 2: device.versionFW = value.toString(); break;
            case 4: device.error = value.toString(); break;
            case 5: device.group_1 = value.toString(); break;
            case 6: device.group_2 = value.toString(); break;
            case 7: device.group_3 = value.toString(); break;
            case 8: device.group_4 = value.toString(); break;
            case 9: device.hight = value.toString(); break;
            case 10: device.tiltAngle = value.toString(); break;
            case 11: device.tiltOnly = value.toString(); break;
            case 12: device.dir = value.toString(); break;
        }
    } else if (info.deviceType == SixChannelDevice && info.deviceIndex >= 0 && info.deviceIndex < m_sixChanelData.size()) {
        SixChanel_t &device = m_sixChanelData[info.deviceIndex];
        Chanel_t* channel = nullptr;

        switch (info.channelIndex) {
            case 0: channel = &device.chanel_1; break;
            case 1: channel = &device.chanel_2; break;
            case 2: channel = &device.chanel_3; break;
            case 3: channel = &device.chanel_4; break;
            case 4: channel = &device.chanel_5; break;
            case 5: channel = &device.chanel_6; break;
        }

        if (channel) {
            // Обновляем соответствующие поля канала
            switch (column) {
                case 0: if (info.channelIndex == 0) device.address = value.toString(); break;
                case 2: if (info.channelIndex == 0) device.versionFW = value.toString(); break;
                case 3: channel->chanel = value.toString(); break;
                case 4: channel->error = value.toString(); break;
                case 5: channel->group_1 = value.toString(); break;
                case 6: channel->group_2 = value.toString(); break;
                case 7: channel->group_3 = value.toString(); break;
                case 8: channel->group_4 = value.toString(); break;
                case 9: channel->hight = value.toString(); break;
                case 10: channel->endangle = value.toString(); break;
                case 11: channel->tiltOnly = value.toString(); break;
                case 12: channel->dir = value.toString(); break;
            }
        }
    }

    // Уведомляем об изменении конкретной строки
    QModelIndex modelIndex = createIndex(row, 0);
    emit dataChanged(modelIndex, modelIndex, {RowDataRole});
}

bool TableModel::saveCSV(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);

    for (const QList<QVariant> &row : m_data) {
        QStringList fields;
        for (const QVariant &field : row) {
            QString text = field.toString();

            // Экранируем поля, содержащие запятые или кавычки
            if (text.contains(',') || text.contains('"') || text.contains('\n')) {
                text.replace('"', "\"\""); // Двойные кавычки
                fields.append('"' + text + '"');
            } else {
                fields.append(text);
            }
        }
        out << fields.join(',') << '\n';
    }

    file.close();
    qDebug() << "Saved" << m_data.size() << "rows to" << filePath;
    return true;
}

// TableModel.cpp
QString TableModel::getRowIcon(int row, bool isSelected) const {
    if (isSelected) return "qrc:/icons/row_selected.png";

    // Дополнительная логика для разных типов строк
    if (row == 0) return "qrc:/icons/header_icon.png";
    return "qrc:/icons/row_default.png";
}
