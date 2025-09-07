#include "serial.h"
#include <QSerialPortInfo>
#include <QDebug>

Serial::Serial(QObject *parent) : QObject(parent)
{
    connect(&serial, &QSerialPort::readyRead, this, &Serial::readData);

    connect(&serial, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
        if (error != QSerialPort::NoError) {
            emit errorOccurred(serial.errorString());
            qDebug() << "Serial port error:" << serial.errorString();
        }
    });
}

Serial::~Serial()
{
    if (serial.isOpen()) {
        serial.close();
    }
}
/**/
void Serial::readPorlList(){
    comPortsList.clear();  // Очищаем перед добавлением
//    for (const QSerialPortInfo &port : QSerialPortInfo::availablePorts()) {

//        comPortsList.append(port.portName());
//    }
     QList<QSerialPortInfo> serialPortInfoList;
    serialPortInfoList = QSerialPortInfo::availablePorts();
    for(int i=0;i<serialPortInfoList.count();i++)
        if(!serialPortInfoList.at(i).isBusy())
                comPortsList.append(serialPortInfoList.at(i).portName());
    qDebug() << "Доступные COM-порты:" << comPortsList;
}

bool Serial::openPort(int index, qint32 baudRate)
{
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
        qDebug() << "Порт открыт:" << portName << "Скорость" << serial.baudRate();
        return true;
    } else {
        qDebug() << "Ошибка открытия порта" << portName << ":" << serial.errorString();
        return false;
    }
}

void Serial::closePort()
{
    if (serial.isOpen()) {
        serial.close();
        qDebug() << "Порт закрыт.";
    }
}

QStringList Serial::getSerialPort()
{
    return comPortsList;
}

bool Serial::sendData(const QString &data)
{
    qDebug() << "sendData QString";
    if (serial.isOpen() && serial.isWritable()) {
        QByteArray byteData = data.toUtf8();
        qint64 bytesWritten = serial.write(byteData);

        if (bytesWritten == -1) {
            qDebug() << "Ошибка отправки данных:" << serial.errorString();
            return false;
        }

        if (!serial.waitForBytesWritten(1000)) {
            qDebug() << "Таймаут отправки данных:" << serial.errorString();
            return false;
        }

        qDebug() << "Отправлено" << bytesWritten << "байт";
        emit dataSent(data);
        return true;
    }
    return false;
}

bool Serial::sendData(const QByteArray &data)
{
    qDebug() << "sendData QByteArray";
    if (serial.isOpen() && serial.isWritable()) {
        qint64 bytesWritten = serial.write(data);

        if (bytesWritten == -1) {
            qDebug() << "Ошибка отправки данных:" << serial.errorString();
            return false;
        }

        if (!serial.waitForBytesWritten(1000)) {
            qDebug() << "Таймаут отправки данных:" << serial.errorString();
            return false;
        }

        qDebug() << "Отправлено" << bytesWritten << "байт";
        emit dataSent(QString::fromUtf8(data));
        return true;
    }
    return false;
}

void Serial::readData()
{
    QByteArray data = serial.readAll();
//    qDebug() << "Получено данных:" << data.size() << "байт";
//    qDebug() << "Данные (HEX):" << data.toHex(' ');

    // Отправляем сырые данные для обработки
    emit rawDataReceived(data);
}

Serial::Settings Serial::settings() const
{
    return m_currentSettings;
}


