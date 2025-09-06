// TableController.cpp
#include "tablecontroller.h"
#include "tablemodel.h"
#include <QDebug>

TableController::TableController(QObject *parent)
    : QObject(parent), m_model(nullptr)
{
}

void TableController::setModel(TableModel *model)
{
    if (m_model != model) {
        m_model = model;
    }
}

void TableController::processRow(int rowIndex)
{
    if (!m_model) {
        qWarning() << "Model is not set!";
        return;
    }

    // Получаем данные непосредственно из модели
    // Используем существующие методы модели
    QModelIndex index = m_model->index(rowIndex, 0);
    QVariant rowData = m_model->data(index, TableModel::RowDataRole);

    if (!rowData.isValid()) {
        qWarning() << "Invalid row data for index:" << rowIndex;
        return;
    }

    // Предполагаем, что rowData - это QList<QVariant>
    QList<QVariant> row = rowData.value<QList<QVariant>>();

    if (row.size() < 10) { // Проверяем, что достаточно данных
        qWarning() << "Row data is too short:" << row.size();
        return;
    }

    qDebug() << "Processing row:" << rowIndex << "Data:" << row;

    // Извлекаем нужные данные (адаптируйте под вашу структуру)
    m_serialText = row.value(0).toString();      // address
    m_minAngleText = row.value(9).toString();    // tiltAngle
    m_typeText = "1-Ch";                         // фиксированное значение
    //m_activationDateText = tr("%1.%2.%3").arg(row.value(9)).arg(row.value(9)).arg(row.value(9));//"08.12.04";           // Сборное значение
    m_activationDateText = row.value(18).toString();

    QString day = row.value(16).toString();
    QString month = row.value(17).toString();
    QString year = row.value(18).toString();
    qDebug() << "Date "<< day << month << year << row.value(16).toString();

    // Здесь можно добавить любую дополнительную обработку

    // Уведомляем об изменении данных
    emit dataProcessed();
}

// Реализация геттеров
QString TableController::serialText() const { return m_serialText; }
QString TableController::minAngleText() const { return m_minAngleText; }
QString TableController::typeText() const { return m_typeText; }
QString TableController::activationDateText() const { return m_activationDateText; }
