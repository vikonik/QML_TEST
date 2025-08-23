#include "serial.h"
//#include "debug.h"
#include <QSerialPortInfo>
#include <QDebug>

Serial::Serial(QObject *parent) : QObject(parent), m_currentDeviceType(UnknownDevice), m_channelsReceived(0) {
    // Конструктор с параметром родительского виджета
//    serialPort = new QSerialPort(this);
//    serialPortInfoList = QSerialPortInfo::availablePorts();
//    serialPort->setBaudRate(115200);
//    connect(this, SIGNAL(readyRead()), this, SLOT(readData()),Qt::DirectConnection);
    connect(&serial, &QSerialPort::readyRead, this, &Serial::readData);

    // Подключение сигналов
    connect(this, &Serial::oneChanelDataReceived, this, [](const OneChanel_t &data) {
        // Обработка данных одноканального устройства
        data.debugPrint();
    });

    connect(this, &Serial::sixChanelDataReceived, this, [](const SixChanel_t &data) {
        // Обработка данных шестиканального устройства
        data.debugPrint();
        // Доступ к данным каналов: data.chanel_1, data.chanel_2, etc.
    });
}

Serial::~Serial() {
    // Очистка
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

/**/
void Serial::baseSetting(){

    for(int i = 0; i < comPortsList.count(); i++){//перебираем доступные порты и определяем что к ним подключено


    }

}

/**/
bool Serial::openPort(int index, qint32 baudRate) {
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
        qDebug() << "Порт открыт:" << portName << "Скорость " << serial.baudRate();

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
        qDebug() << "Отправлено " << bytesWritten << "байт";
        qDebug() << QString::fromUtf8(*data);
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
QByteArray m_buffer;
void Serial::readData() {
    QByteArray data = serial.readAll();
    m_buffer.append(data);
    QString receivedString = QString::fromUtf8(data);

 //   qDebug() << "Data received:" << receivedString;
    //emit dataReceived(receivedString);
    processBuffer();
}

/**/

void Serial::processBuffer()
{
    // Парсим буфер для извлечения полных блоков данных
    // Начало блока: 0x0D 0x0A (CR LF)
    // Конец блока: 0x3C ('<')

    while (true) {
        // Ищем начало блока (CR LF)
        int startIndex = m_buffer.indexOf("\x0D\x0A");
        if (startIndex == -1) {
            // Начало блока не найдено
            break;
        }

        // Ищем конец блока после начала
        int endIndex = m_buffer.indexOf('\x3C', startIndex + 3);
        if (endIndex == -1) {
            // Конец блока не найден
            break;
        }

        // Извлекаем полный блок (исключая маркеры начала и конца)
        QByteArray block = m_buffer.mid(startIndex + 3, endIndex - startIndex - 3);

        QString dataString = QString::fromLatin1(block);

        qDebug() << "Получены данные:" << dataString;


        // Определяем тип устройства
        if (m_currentDeviceType == UnknownDevice) {
            m_currentDeviceType = identifyDevice(dataString);
        }

        // Обрабатываем данные в зависимости от типа устройства
        if (m_currentDeviceType == OneChanelDevice) {
            OneChanel_t deviceData;
            if (deviceData.parseFromString(dataString)) {
                deviceData.debugPrint();
                emit oneChanelDataReceived(deviceData);
                m_currentDeviceType = UnknownDevice; // Сбрасываем для следующего пакета
            } else {
                qDebug() << "Ошибка парсинга данных одноканального устройства";
            }
        }
        else if (m_currentDeviceType == SixChanelDevice) {
           qDebug() << "SixChanelDevice" << "dataString.length() = " << dataString.length() ;

            if (dataString.startsWith("0000") && dataString.length() == 16) {
                qDebug()<<"SixChanelDeviceHeader";
                // Это заголовок шестиканального устройства
                if (m_sixChanelData.parseHeaderFromString(dataString)) {
                    m_sixChanelData.debugPrint();
                    m_channelsReceived = 0;
                }
            }
            else if (dataString.length() == 36) {
                qDebug()<<"SixChanelDeviceChanel" << m_channelsReceived;
                // Это данные канала
                if (m_channelsReceived < 6) {
                    Chanel_t channelData;
                    if (channelData.parseFromString(dataString)) {
                        // Сохраняем данные канала в соответствующую структуру
                        switch (m_channelsReceived) {
                            case 0: m_sixChanelData.chanel_1 = channelData; break;
                            case 1: m_sixChanelData.chanel_2 = channelData; break;
                            case 2: m_sixChanelData.chanel_3 = channelData; break;
                            case 3: m_sixChanelData.chanel_4 = channelData; break;
                            case 4: m_sixChanelData.chanel_5 = channelData; break;
                            case 5: m_sixChanelData.chanel_6 = channelData; break;
                        }
                        m_channelsReceived++;

                        // Если получили все 6 каналов, отправляем данные
                        if (m_channelsReceived == 6) {
                            qDebug() << "m_channelsReceived";
                            emit sixChanelDataReceived(m_sixChanelData);
                            m_currentDeviceType = UnknownDevice; // Сбрасываем для следующего пакета
                        }
                    }
                }
            }
        }







        // Удаляем обработанную часть из буфера (включая маркеры)
        m_buffer.remove(0, endIndex + 1);

        // Отправляем извлеченный блок
 //       emit blockReceived(block);
 //       emit dataReceived(QString::fromLatin1(block));
        qDebug() <<  QString::fromUtf8(block);
    }

    // Если буфер становится слишком большим (нет маркеров долгое время),
    // можно очистить его для предотвращения переполнения
    if (m_buffer.size() > 1024) {
        qDebug() << "Буфер слишком большой, очистка. Возможно потеря данных.";
        m_buffer.clear();
    }
}

/**/

Serial::DeviceType Serial::identifyDevice(const QString &data)
{
    qDebug() << "identifyDevice" << "data.length() = "<<data.length() << "data.at(4) = " << data.at(4);

    if (data.length() == 49 && data.startsWith("0000") && data.at(4) == 'A') {
        return OneChanelDevice;
    }
    else if (data.length() == 16 && data.startsWith("0000") && data.at(4) == 'B') {
        return SixChanelDevice;
    }
    return UnknownDevice;
}
