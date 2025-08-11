#include "tablemodel.h"
#include <QTextStream>
#include <QDebug>
#include <QAbstractTableModel>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

const int TableModel::COLUMN_COUNT;
const int TableModel::BATCH_SIZE;


TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent) {

    // Путь к файлу данных
        QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(dataDir);
       // QString dataPath = "D:/0_KNX/QML_test/QML_Test/tabledata.csv";
         QString dataPath = "D:/Project/99_QML_Table/QML_TEST/QML_test/tabledata.csv";
        //QString dataPath =  "tabledata.csv";
        // Проверяем существование файла
        if (!QFile::exists(dataPath)) {
            qDebug() << "create new file ";
            // Создаем новый файл с заголовками
            QFile file(dataPath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                // Заголовки столбцов
                QStringList headers;
                for (int i = 1; i <= 15; i++) {
                    headers << QString("Column %1").arg(i);
                }
                out << headers.join(';') << "\n";

                // Заполняем 10 строк по 15 столбцов
                for (int row = 0; row < 10; ++row) {
                    QStringList rowData;
                    for (int col = 1; col <= 15; ++col) {
                        rowData << QString("R%1_C%2").arg(row + 1).arg(col);
                    }
                    out << rowData.join(';') << "\n";
                }

                file.close();
            }
        }
        else{
           qDebug() << "file exist ";

        }

        // Загружаем данные
        loadFromFile(dataPath);

        if (!m_data.isEmpty()) {

            selectRow(1);

        }
}

int TableModel::rowCount(const QModelIndex &) const {
    //return m_rowsLoaded;
    return m_data.size();
}

int TableModel::columnCount(const QModelIndex &) const {
    return COLUMN_COUNT;
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column);
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
//        for (const auto &row : m_data) {
//            qDebug() << row;
//        }
        qDebug() << "index.row()][index.column():" << m_data[index.row()][index.column()] << index.row() << index.column();
        return m_data[index.row()][index.column()];

    case IsSelectedRole:
        return index.row() == m_selectedRow;

    default:
        return QVariant();
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole || index.row() >= m_data.size())
        return false;

    if (!editableColumns.contains(index.column()))
        return false;

    if (role == IsSelectedRole) {
        return index.row() == m_selectedRow;
    }

    m_data[index.row()][index.column()] = value.toString();
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
//    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
//    if (!index.isValid())
//        return defaultFlags;

//    if (editableColumns.contains(index.column()))
//        return defaultFlags | Qt::ItemIsEditable;

//    return defaultFlags;
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (editableColumns.contains(index.column()))
        flags |= Qt::ItemIsEditable;
    return flags;
}

QHash<int, QByteArray> TableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole]   = "display";
    roles[Qt::EditRole]      = "edit";
    roles[IsSelectedRole]    = "isSelected";   // Новая роль для выделения строки
  //  roles[IsUnSelectedRole]  = "isUnSelected";
    return roles;
}

bool TableModel::canFetchMore(const QModelIndex &) const {
//    return m_rowsLoaded < m_totalRows;
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QTextStream in(&file);
    int totalLines = 0;
    while (!in.atEnd()) {
        in.readLine();
        totalLines++;
    }
    file.close();

    return m_data.size() < totalLines;
}

void TableModel::fetchMore(const QModelIndex &) {
//    int remaining = m_totalRows - m_rowsLoaded;
//    int toFetch = qMin(BATCH_SIZE, remaining);

//    if (toFetch <= 0) return;

//    beginInsertRows(QModelIndex(), m_rowsLoaded, m_rowsLoaded + toFetch - 1);
//    m_rowsLoaded += toFetch;
//    endInsertRows();
    loadBatch(m_data.size(), BATCH_SIZE);
}

bool TableModel::loadFromFile(const QString& filePath) {
//    QString actualPath = filePath;
//    if (actualPath.isEmpty()) actualPath = "tabledata.csv";

//    QFile file(filePath);
//    if (!file.open(QIODevice::ReadOnly)) {
//        qWarning() << "Failed to open file:" << filePath;
//        return false;
//    }

//    beginResetModel();
//qDebug() << "im here ";
//    m_data.clear();
//    m_filePath = filePath;

//    QTextStream in(&file);
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        QStringList fields = line.split(';');
//        while (fields.size() < COLUMN_COUNT) fields << "";
//        m_data.append(fields);
//    }

//    m_totalRows = m_data.size();
//    m_rowsLoaded = qMin(BATCH_SIZE, m_totalRows);
////qDebug() << m_data;
//    endResetModel();
//    return true;
    QString path = filePath.isEmpty() ? m_filePath : filePath;
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open file:" << path;
            return false;
        }

        beginResetModel();
        m_data.clear();

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(';');
            while (fields.size() < COLUMN_COUNT) fields << "";
            m_data.append(fields);
        }
        file.close();

        endResetModel();
        for (const QStringList &row : m_data) {
            qDebug() << row;
        }
        return true;
}

void TableModel::loadBatch(int start, int count) {
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    beginInsertRows(QModelIndex(), start, start + count - 1);

    QTextStream in(&file);
    // Пропустить первые 'start' строк
    for (int i = 0; i < start && !in.atEnd(); i++) {
        in.readLine();
    }

    // Загрузить 'count' строк
    for (int i = 0; i < count && !in.atEnd(); i++) {
        QString line = in.readLine();
        QStringList fields = line.split(';');
        while (fields.size() < COLUMN_COUNT) fields << "";
        m_data.append(fields);
    }

    endInsertRows();
    file.close();
}

void TableModel::selectRow(int row) {
        qDebug() << "Selecting row:" << row;

        if (row < 0 || row >= rowCount())
            return;

        int previous = m_selectedRow;
        if (previous == row)
            return; // ничего не меняется, обновлять не надо

        m_selectedRow = row;

        QVector<int> roles = { IsSelectedRole };

        // Обновляем предыдущую выбранную строку
        if (previous >= 0) {
            emit dataChanged(index(previous, 0), index(previous, columnCount() - 1), roles);
        }

        // Обновляем новую выбранную строку
        emit dataChanged(index(row, 0), index(row, columnCount() - 1), roles);

        emit rowSelected(row);

        emit selectedRowChanged(row);
        qDebug() << "Updated selection from" << previous << "to" << row << "for roles:" << roles;


}



