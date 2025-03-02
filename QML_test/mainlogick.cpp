#include "mainlogick.h"
#include "debug.h"
#include "serial.h"
#include <QDebug>
#include<QString>

MainLogick::MainLogick()
{
    qDebug() << "MainLogick";
     debugWindow = new Debug();
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

}
