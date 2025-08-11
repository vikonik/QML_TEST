#include "tablemodel.h"
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

TableModel::TableModel(QObject *parent) : QAbstractListModel(parent)
{
    QString dataPath = "D:/0_KNX/QML_test/QML_Test/tabledata.csv";

    if (!QFile::exists(dataPath)) {
        // Создание файла с тестовыми данными
        QFile file(dataPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QStringList headers;
            for (int i = 1; i <= 15; i++) {
                headers << QString("Column %1").arg(i);
            }
            out << headers.join(';') << "\n";

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

    loadFromFile(dataPath);
    if (!m_data.isEmpty()) {
        selectRow(1);
    }
}

int TableModel::rowCount(const QModelIndex &) const
{
    return m_data.size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    switch (role) {
    case DisplayRole:
        return m_data[index.row()];
    case IsSelectedRole:
        return index.row() == m_selectedRow;
    default:
        return QVariant();
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != DisplayRole || index.row() >= m_data.size())
        return false;

    m_data[index.row()] = value.toStringList();
    emit dataChanged(index, index, {role});
    return true;
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DisplayRole] = "display";
    roles[IsSelectedRole] = "isSelected";
    return roles;
}

bool TableModel::isColumnEditable(int column) const
{
    return editableColumns.contains(column);
}

bool TableModel::loadFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
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
    return true;
}

void TableModel::selectRow(int row)
{
    if (row < 0 || row >= rowCount()) return;

    int previous = m_selectedRow;
    if (previous == row) return;

    m_selectedRow = row;
    QVector<int> roles = { IsSelectedRole };

    if (previous >= 0) {
        emit dataChanged(index(previous, 0), index(previous, 0), roles);
    }

    emit dataChanged(index(row, 0), index(row, 0), roles);
    emit selectedRowChanged(row);
}
