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
Получаем данные из DataParser
*/
void TableModel::loadDeviceData(const QVector<OneChanel_t>& data){

    qDebug()<<"I am here";
    beginResetModel();
    // Очищаем существующие данные
        m_data.clear();
        m_fullData = data; // Сохраняем полные данные
        // Заполняем модель данными из вектора
        for (const OneChanel_t &device : data) {
            QList<QVariant> row;
            row.append(device.address);    // Добавляем адрес
            row.append("Device");
            row.append(device.versionFW);  // Добавляем версию firmware
            row.append("1");//Номер канада
            row.append(device.error);
            row.append(device.group_1);
            row.append(device.group_2);
            row.append(device.group_3);
            row.append(device.group_4);
            row.append(device.hight);
            row.append(device.tiltAngle);//Tilt
            row.append(device.tiltOnly);
            row.append(device.dir);//Motor Revers


            // Добавляем строку в модель
            m_data.append(row);
            qDebug() << "++";
        }
        endResetModel();
        qDebug() << "Loaded" << m_data.size() << "rows from dataParser" ;
}

/**/
// Добавляем метод для получения полных данных
QVector<OneChanel_t> TableModel::getFullData() const {
    return m_fullData;
}
/**/
void TableModel::clear() {
    beginResetModel();
    m_data.clear();
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

    // Для 6-й колонки преобразуем значение в "1" или "0"
//    if (column == 5) {
//        m_data[row][column] = value.toBool() ? "1" : "0";
//    } else {
//        m_data[row][column] = value;
//    }

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
