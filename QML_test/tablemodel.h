#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QStringList>
#include <QSet>

class TableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    // Свойства и методы
    Q_PROPERTY(int selectedRow READ selectedRow NOTIFY selectedRowChanged)
    Q_INVOKABLE void selectRow(int row);
    Q_INVOKABLE bool isColumnEditable(int column) const;
    int selectedRow() const { return m_selectedRow; }

    // Работа с файлом
    Q_INVOKABLE bool loadFromFile(const QString& filePath);

    enum Roles {
        DisplayRole = Qt::UserRole + 1,
        IsSelectedRole
    };

signals:
    void selectedRowChanged(int row);

private:
    QVector<QStringList> m_data;
    int m_selectedRow = -1;
    QString m_filePath;

    static const int COLUMN_COUNT = 15;
    QSet<int> editableColumns{2, 4, 6, 8, 10};
};

#endif // TABLEMODEL_H
