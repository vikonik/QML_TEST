#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include "dataStruct.h"

class TableModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QVariantList editableColumns READ editableColumns WRITE setEditableColumns NOTIFY editableColumnsChanged)

public:
    explicit TableModel(QObject *parent = nullptr);

    // Роли для доступа к данным
    enum Roles {
        RowDataRole = Qt::UserRole + 1
    };

    // Типы устройств
    enum DeviceType {
        OneChannelDevice,
        SixChannelDevice
    };

    // Структура для хранения информации о строке
    struct TableRowInfo {
        DeviceType deviceType;
        int deviceIndex;
        int channelIndex; // Для многоканальных устройств
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadCSV(const QString &filePath);
    Q_INVOKABLE void addRow(const QList<QVariant> &row);
    Q_INVOKABLE void clear();

    // Для редактируемых столбцов
    QVariantList editableColumns() const;
    void setEditableColumns(const QVariantList &columns);

    Q_INVOKABLE bool isCellEditable(int row, int column) const;
    Q_INVOKABLE void updateCell(int row, int column, const QVariant &value);
    // Добавляем метод сохранения
    Q_INVOKABLE bool saveCSV(const QString &filePath);
    // Переименованный метод, чтобы избежать конфликта
    void setModelData(const QList<QList<QVariant>> &newData);

    Q_INVOKABLE QString getRowIcon(int row, bool isSelected) const;
    QVector<OneChanel_t> getOneChanelData() const;
    QVector<SixChanel_t> getSixChanelData() const;

    // Новые методы для работы с обоими типами устройств
    void addOneChanelDevice(const OneChanel_t &device);
    void addSixChanelDevice(const SixChanel_t &device);
    TableRowInfo getRowInfo(int row) const;

public slots:
    void loadOneChanelData(const QVector<OneChanel_t> &data);
    void loadSixChanelData(const QVector<SixChanel_t> &data);

signals:
    void editableColumnsChanged();

private:
    QList<QList<QVariant>> m_data;
    QList<int> m_editableColumns; // Индексы редактируемых столбцов

    // Для хранения полных данных обоих типов
    QVector<OneChanel_t> m_oneChanelData;
    QVector<SixChanel_t> m_sixChanelData;
    QVector<TableRowInfo> m_rowInfo; // Информация о типах строк

    void rebuildTableData();
};

#endif // TABLEMODEL_H
