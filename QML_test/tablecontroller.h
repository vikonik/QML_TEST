#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
// TableController.h
#include <QObject>
#include <QModelIndex>
#include "dataparser.h"
// Предварительное объявление класса
class TableModel;

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

public slots:
    void processRow(int rowIndex);
    void updateSerialValue(const QString &newValue);
    void setSelectedRow(int row);

signals:
    void dataProcessed();
    void selectedRowChanged();

private:
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
