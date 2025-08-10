#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>
#include <QFile>
#include <QSet>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);
    // Добавляем свойство для доступа к выбранной строке из QML
    Q_PROPERTY(int selectedRow READ selectedRow NOTIFY selectedRowChanged)

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;


    QHash<int, QByteArray> roleNames() const override;

    // Динамическая подгрузка
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    // Работа с файлом
    Q_INVOKABLE bool loadFromFile(const QString& filePath);
//    Q_INVOKABLE bool saveToFile(const QString& filePath);

    // Выбор строки
    Q_INVOKABLE void selectRow(int row);
    int selectedRow() const { return m_selectedRow; }

    Q_INVOKABLE bool isColumnEditable(int column) const {
        return editableColumns.contains(column);
    }

    enum CustomRoles {
        IsSelectedRole = Qt::UserRole + 1

    };

signals:
    void rowSelected(int row);
//    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void selectedRowChanged(int row);

private:
    QVector<QStringList> m_data;
    int m_selectedRow = -1;
    QString m_filePath;
    int m_totalRows = 0;
    int m_rowsLoaded = 0;

    static const int COLUMN_COUNT = 15;
    static const int BATCH_SIZE = 50;


    // Столбцы, доступные для редактирования
    QSet<int> editableColumns{2, 4, 6, 8, 10};
    void loadBatch(int start, int count);
};

#endif // TABLEMODEL_H
