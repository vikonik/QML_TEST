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

public:
    explicit TableController(QObject *parent = nullptr);

    // Устанавливаем модель
    void setModel(TableModel *model);

    void setDataParser(DataParser *dataParser); // Новый метод

    // Геттеры для свойств
    QString serialText() const;
    QString minAngleText() const;
    QString typeText() const;
    QString activationDateText() const;

public slots:
    void processRow(int rowIndex);

signals:
    void dataProcessed();

private:
    TableModel *m_model;
    DataParser *m_dataParser;
    QString m_serialText;
    QString m_minAngleText;
    QString m_typeText;
    QString m_activationDateText;
};


#endif // TABLECONTROLLER_H
