#ifndef MAINLOGICK_H
#define MAINLOGICK_H

#include <QObject>
#include "debug.h"
#include "serial.h"
#include "fifo.h"
#include "rfmax.h"

class MainLogick: public QObject {
    Q_OBJECT

public:
    explicit MainLogick(QObject *parent = nullptr);

    Debug *debugWindow;

signals:
    void signalSendData(QByteArray *data);
//    void signalSendData(QString *data);

public slots:
    void scanNet();
    void detectDeviceType(QByteArray *data);

private:

    #define CH_1    "A"
    #define CH_6    "B"
    #define RFMAX   "W"
    #define IRMAX   "R"

    FIFO<2048> fifo;
    Serial *serial;
    RFMax *rfMax;
    QString deviceType;//последий определеннфый тип
    void setConnect();

};

#endif // MAINLOGICK_H
