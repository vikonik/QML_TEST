#include "mainlogick.h"
#include "debug.h"
#include "serial.h"
#include <QDebug>
#include<QString>
#include <QObject> // Это важно для работы с сигналами и слотами


MainLogick::MainLogick(QObject *parent) : QObject(parent)
{
    qDebug() << "MainLogick";
    rfMax = new RFMax();
     debugWindow = new Debug();
     deviceType.clear();
    debugWindow->show();

    debugWindow->log(QString("MainLogick"));
    serial = new Serial();
    serial->readPorlList();
    QStringList comPorts = serial->getSerialPort();
    // Проверяем, что список не пуст
    if (!comPorts.isEmpty()) {
        QString logString = comPorts.join("\n");  // Преобразуем список в строку
        // Выводим лог
        debugWindow->log(QString("Найденные COM-порты"));
        debugWindow->log(logString);
    } else {
        // Если список пуст
        QString errorMessage = "No COM ports available!";

        // Выводим сообщение об ошибке
        debugWindow->log(errorMessage);
    }

    setConnect();

}

/*
Настраиваем connect
*/
void MainLogick::setConnect(){
    connect(this, SIGNAL(signalSendData(QByteArray*)), serial, SLOT(sendData(QByteArray*)));
//connect(this, &MainLogick::signalSendData, serial, &Serial::sendData);
//connect(this, &MainLogick::signalSendData, serial, &Serial::sendData);

}


/*
Отправляем запрос на сканирование сети
*/
void MainLogick::scanNet(){
    QByteArray command;
    command.append(">Scan?<");
    emit signalSendData(&command);
}

/*
Определяем что за устройство
*/
void MainLogick::detectDeviceType(QByteArray *data){

    uint8_t tmp;
    //положили полученный данные а буфер
    for (char byte : *data) {
        if (!fifo.isFull()) {
            fifo.push(static_cast<uint8_t>(byte));
        } else {
            fifo.flush();
            break; // Останавливаемся, если FIFO заполнен
        }
    }

    //ищем начало команды
    QString marker = "\r\n>";
    QString compData;
    size_t n = 0;

    do{
        compData.append(fifo.getN(n));
        compData.append(fifo.getN(n+1));
        compData.append(fifo.getN(n+2));
        n++;

    } while(!!QString::compare(marker, compData) || fifo.count() < n );

    //Если не нашли начала, то это или продолжение пакета или не полные данные
    if(n >= fifo.count() && deviceType.isEmpty())
        return;
    //Ecли начало нашли
    if(n < fifo.count()){
        n -= 1;
        fifo.shiftTail(n);//переставили хвост на начало команды
        //определяем тип устройства
        deviceType.append(fifo.getN(7));// 7 - смещеие в массиве для чтения типа устройства

    }
    else if(!deviceType.isEmpty()){

        if(!QString::compare(deviceType, CH_1)){

        }
        else if(!QString::compare(deviceType, CH_6)){

        }
        else if(!QString::compare(deviceType, RFMAX)){
            if(!rfMax->detected){
                rfMax->currentAddr = 0;
                memset(rfMax->rfMax, 0, rfMax->getSizeRFMAX_Type());//Очистили структуру
                rfMax->detected = true;
            }
            while(!fifo.isEmpty()){
                uint8_t* basePtr = reinterpret_cast<uint8_t*>(&rfMax->rfMax);//получили удрес структуры
                basePtr[rfMax->currentAddr++] = fifo.front(); // Записываем байт в структуру
                fifo.pop();

            }



        }
        else if(!QString::compare(deviceType, IRMAX)){

        }
        else
            return;

    }
}


