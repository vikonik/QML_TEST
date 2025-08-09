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
       // QString dataPath = dataDir + "/tabledata.csv";
        QString dataPath =  "tabledata.csv";
qDebug() << "dataPath " + dataPath;
qDebug() << "Working directory:" << QDir::currentPath();
qDebug() << "QCoreApplication::applicationDirPath():" << QCoreApplication::applicationDirPath();
        // Проверяем существование файла
        if (!QFile::exists(dataPath)) {
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
                file.close();
            }
        }

        // Загружаем данные
        loadFromFile(dataPath);
}

int TableModel::rowCount(const QModelIndex &) const {
    return m_rowsLoaded;
}

int TableModel::columnCount(const QModelIndex &) const {
    return COLUMN_COUNT;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_rowsLoaded || index.column() >= COLUMN_COUNT)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.row() < m_data.size()) {
            return m_data[index.row()][index.column()];
        }
        return QString("Loading...");
    }

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || role != Qt::EditRole || index.row() >= m_data.size())
        return false;

    if (!editableColumns.contains(index.column()))
        return false;

    m_data[index.row()][index.column()] = value.toString();
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (!index.isValid())
        return defaultFlags;

    if (editableColumns.contains(index.column()))
        return defaultFlags | Qt::ItemIsEditable;

    return defaultFlags;
}

QHash<int, QByteArray> TableModel::roleNames() const {
    return {
        {Qt::DisplayRole, "display"},
        {Qt::EditRole, "edit"}
    };
}

bool TableModel::canFetchMore(const QModelIndex &) const {
    return m_rowsLoaded < m_totalRows;
}

void TableModel::fetchMore(const QModelIndex &) {
    int remaining = m_totalRows - m_rowsLoaded;
    int toFetch = qMin(BATCH_SIZE, remaining);

    if (toFetch <= 0) return;

    beginInsertRows(QModelIndex(), m_rowsLoaded, m_rowsLoaded + toFetch - 1);
    m_rowsLoaded += toFetch;
    endInsertRows();
}

bool TableModel::loadFromFile(const QString& filePath) {
    QString actualPath = filePath;
    if (actualPath.isEmpty()) actualPath = "tabledata.csv";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    beginResetModel();

    m_data.clear();
    m_filePath = filePath;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(';');
        while (fields.size() < COLUMN_COUNT) fields << "";
        m_data.append(fields);
    }

    m_totalRows = m_data.size();
    m_rowsLoaded = qMin(BATCH_SIZE, m_totalRows);

    endResetModel();
    return true;
}

void TableModel::selectRow(int row) {
    if (row < 0 || row >= m_rowsLoaded) return;

    int oldRow = m_selectedRow;
    m_selectedRow = row;

    if (oldRow >= 0) {
        QModelIndex topLeft = createIndex(oldRow, 0);
        QModelIndex bottomRight = createIndex(oldRow, COLUMN_COUNT - 1);
        emit dataChanged(topLeft, bottomRight);
    }

    QModelIndex topLeft = createIndex(row, 0);
    QModelIndex bottomRight = createIndex(row, COLUMN_COUNT - 1);
    emit dataChanged(topLeft, bottomRight);

    emit rowSelected(row);
}
