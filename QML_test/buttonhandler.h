#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QDebug>

class ButtonHandler : public QObject {
    Q_OBJECT
public:
    explicit ButtonHandler(QObject *parent = nullptr);

signals:
    void buttonClicked(const QString &buttonName);  // Сигнал, который будет отправляться

public slots:
    void onButtonClicked(const QString &buttonId);
};

#endif // BUTTONHANDLER_H
