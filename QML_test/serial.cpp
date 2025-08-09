#include "serial.h"
//#include "debug.h"
#include <QSerialPortInfo>
#include <QDebug>

Serial::Serial(QObject *parent) : QObject(parent) {
    // Конструктор с параметром родительского виджета
}

Serial::~Serial() {
    // Очистка
}

/**/
void Serial::readPorlList(){
    comPortsList.clear();  // Очищаем перед добавлением
    for (const QSerialPortInfo &port : QSerialPortInfo::availablePorts()) {
        comPortsList.append(port.portName());
    }
    qDebug() << "Доступные COM-порты:" << comPortsList;
}

/**/
void Serial::baseSetting(){

    for(int i = 0; i < comPortsList.count(); i++){//перебираем доступные порты и определяем что к ним подключено


    }

}

/**/
bool Serial::openPort(int index, qint32 baudRate = QSerialPort::Baud9600) {
    if (index < 0 || index >= comPortsList.size()) {
        qDebug() << "Ошибка: Неверный индекс порта!";
        return false;
    }

    QString portName = comPortsList.at(index);
    serial.setPortName(portName);
    serial.setBaudRate(baudRate);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Порт открыт:" << portName;
        return true;
    } else {
        qDebug() << "Ошибка открытия порта" << portName << ":" << serial.errorString();
        return false;
    }
}

void Serial::closePort() {
    if (serial.isOpen()) {
        serial.close();
        qDebug() << "Порт закрыт.";
    }
}

/**/
QStringList Serial::getSerialPort(){
 return comPortsList;
}

/**/
bool Serial::sendData(QByteArray *data) {
    if (serial.isOpen()) {
        qint64 bytesWritten = serial.write(*data);
    }
    return 1;
}

/**/
bool Serial::sendData(const QString &data) {
    if (serial.isOpen()) {
        QByteArray byteData = data.toUtf8();
        qint64 bytesWritten = serial.write(byteData);


    }
    return 1;
}

/**/
void Serial::readData() {
    QByteArray data = serial.readAll();
    QString receivedString = QString::fromUtf8(data);

    qDebug() << "Data received:" << receivedString;
    emit dataReceived(receivedString);
}
