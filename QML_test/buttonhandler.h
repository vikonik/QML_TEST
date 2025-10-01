#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QDebug>
#include "tablecontroller.h"

class ButtonHandler : public QObject {
    Q_OBJECT

public:
    explicit ButtonHandler(QObject *parent = nullptr);

    void setTableController(TableController *controller);
signals:
    void buttonClicked(const QString &buttonName);  // Сигнал, который будет отправляться
    void signalSkanID();
    void signalConnect();
    void signalDisconnect();
    void signalReadRequest(const QString &serialID);
    void signalProgramRequest(const QString &deviceData);  // Измененный сигнал с QString

public slots:
    void onButtonClicked(const QString &buttonId);
    void print();

private:
    TableController* m_tableController;
    void handleReadButton();
    void handleProgramButton();
    QString serializeOneChannelData() const;  // Сериализация 1-канального устройства
    QString serializeSixChannelData() const;  // Сериализация 6-канального устройства
};

#endif // BUTTONHANDLER_H
