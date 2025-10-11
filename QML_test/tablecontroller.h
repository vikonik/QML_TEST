#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include <QModelIndex>
#include "dataparser.h"
#include "tablemodel.h"

class TableController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serialText READ serialText NOTIFY dataProcessed)
    Q_PROPERTY(QString minAngleText READ minAngleText NOTIFY dataProcessed)
    Q_PROPERTY(QString typeText READ typeText NOTIFY dataProcessed)
    Q_PROPERTY(QString activationDateText READ activationDateText NOTIFY dataProcessed)
    Q_PROPERTY(int selectedRow READ selectedRow WRITE setSelectedRow NOTIFY selectedRowChanged)

public:
    explicit TableController(QObject *parent = nullptr);

    // Геттеры для свойств
    QString serialText() const;
    QString minAngleText() const;
    QString typeText() const;
    QString activationDateText() const;
    int selectedRow() const;

    // Установка модели и парсера
    void setModel(TableModel *model);
    void setDataParser(DataParser *dataParser);
    QString getSerialIDForRow(int row) const;

    TableModel* model() const { return m_model; }

public slots:
    void processRow(int rowIndex);
    void updateSerialValue(const QString &newValue);
    void setSelectedRow(int row);

    void updateCellsInRange(int startRow, int startCol, int endRow, int endCol, const QString &value);
    void defaultSetupSelectedRow();
signals:
    void dataProcessed();
    void selectedRowChanged();

private:
    QString getSerialFromOneChannel(int deviceIndex) const;
    QString getSerialFromSixChannel(int deviceIndex) const;

    TableModel *m_model;
    DataParser *m_dataParser;
    int m_selectedRow;

    QString m_serialText;
    QString m_minAngleText;
    QString m_typeText;
    QString m_activationDateText;

    void resetDisplayValues();
};

#endif // TABLECONTROLLER_H
