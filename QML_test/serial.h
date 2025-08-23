#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
//#include <QDialog>
#include <QSerialPort>
#include <QDebug>

typedef struct {
    QString address;       // 4
    QString type;          // 1
    QString flag;          // 1
    QString versionFW;     // 1
    QString group_1;       // 4
    QString group_2;       // 4
    QString group_3;       // 4
    QString group_4;       // 4
    QString steps;         // 2
    QString endangle;      // 2
    QString hight;         // 3
    QString tiltOnly;      // 1
    QString SAR;           // 1
    QString currentPosition; // 3
    QString error;         // 2
    QString voltage;       // 3
    QString day;           // 2
    QString month;         // 2
    QString year;          // 4
    QString BR;            // 1
    QString dir;           // 1

    // Метод для парсинга данных из строки
    bool parseFromString(const QString &data) {
        if (data.length() != 49) { // Общая длина всех полей
            qDebug() << "Неверная длина данных. Ожидается 49 символов, получено:" << data.length();
            return false;
        }

        int pos = 0;
        address = data.mid(pos, 4); pos += 4;
        type = data.mid(pos, 1); pos += 1;
        flag = data.mid(pos, 1); pos += 1;
        versionFW = data.mid(pos, 1); pos += 1;
        group_1 = data.mid(pos, 4); pos += 4;
        group_2 = data.mid(pos, 4); pos += 4;
        group_3 = data.mid(pos, 4); pos += 4;
        group_4 = data.mid(pos, 4); pos += 4;
        steps = data.mid(pos, 2); pos += 2;
        endangle = data.mid(pos, 2); pos += 2;
        hight = data.mid(pos, 3); pos += 3;
        tiltOnly = data.mid(pos, 1); pos += 1;
        SAR = data.mid(pos, 1); pos += 1;
        currentPosition = data.mid(pos, 3); pos += 3;
        error = data.mid(pos, 2); pos += 2;
        voltage = data.mid(pos, 3); pos += 3;
        day = data.mid(pos, 2); pos += 2;
        month = data.mid(pos, 2); pos += 2;
        year = data.mid(pos, 4); pos += 4;
        BR = data.mid(pos, 1); pos += 1;
        dir = data.mid(pos, 1); pos += 1;

        return true;
    }

    // Метод для отладки
    void debugPrint() const {
        qDebug() << "Address:" << address;
        qDebug() << "Type:" << type;
        qDebug() << "Flag:" << flag;
        qDebug() << "Version FW:" << versionFW;
        qDebug() << "Group 1:" << group_1;
        qDebug() << "Group 2:" << group_2;
        qDebug() << "Group 3:" << group_3;
        qDebug() << "Group 4:" << group_4;
        qDebug() << "Steps:" << steps;
        qDebug() << "End Angle:" << endangle;
        qDebug() << "Hight:" << hight;
        qDebug() << "Tilt Only:" << tiltOnly;
        qDebug() << "SAR:" << SAR;
        qDebug() << "Current Position:" << currentPosition;
        qDebug() << "Error:" << error;
        qDebug() << "Voltage:" << voltage;
        qDebug() << "Day:" << day;
        qDebug() << "Month:" << month;
        qDebug() << "Year:" << year;
        qDebug() << "BR:" << BR;
        qDebug() << "Dir:" << dir;
    }
} OneChanel_t;


/*
6-ти канальный контроллер
*/
// Структура для канала
typedef struct {
    QString address;       // 4
    QString chanel;        // 1
    QString group_1;       // 4
    QString group_2;       // 4
    QString group_3;       // 4
    QString group_4;       // 4
    QString steps;         // 2
    QString endangle;      // 2
    QString hight;         // 3
    QString tiltOnly;      // 1
    QString SAR;           // 1
    QString currentPosition; // 3
    QString error;         // 2
    QString dir;           // 1

    bool parseFromString(const QString &data) {
        if (data.length() != 36) return false;

        int pos = 0;
        address = data.mid(pos, 4); pos += 4;
        chanel = data.mid(pos, 1); pos += 1;
        group_1 = data.mid(pos, 4); pos += 4;
        group_2 = data.mid(pos, 4); pos += 4;
        group_3 = data.mid(pos, 4); pos += 4;
        group_4 = data.mid(pos, 4); pos += 4;
        steps = data.mid(pos, 2); pos += 2;
        endangle = data.mid(pos, 2); pos += 2;
        hight = data.mid(pos, 3); pos += 3;
        tiltOnly = data.mid(pos, 1); pos += 1;
        SAR = data.mid(pos, 1); pos += 1;
        currentPosition = data.mid(pos, 3); pos += 3;
        error = data.mid(pos, 2); pos += 2;
        dir = data.mid(pos, 1); pos += 1;

        return true;
    }
} Chanel_t;

// Структура для шестиканального устройства
typedef struct {
    QString address;       // 4
    QString type;          // 1
    QString flag;          // 1
    QString versionFW;     // 1
    QString day;           // 2
    QString month;         // 2
    QString year;          // 4
    QString BR;            // 1
    Chanel_t chanel_1;
    Chanel_t chanel_2;
    Chanel_t chanel_3;
    Chanel_t chanel_4;
    Chanel_t chanel_5;
    Chanel_t chanel_6;

    bool parseHeaderFromString(const QString &data) {
        if (data.length() != 16) return false;

        int pos = 0;
        address = data.mid(pos, 4); pos += 4;
        type = data.mid(pos, 1); pos += 1;
        flag = data.mid(pos, 1); pos += 1;
        versionFW = data.mid(pos, 1); pos += 1;
        day = data.mid(pos, 2); pos += 2;
        month = data.mid(pos, 2); pos += 2;
        year = data.mid(pos, 4); pos += 4;
        BR = data.mid(pos, 1); pos += 1;

        return true;
    }

    void debugPrint() const {
        qDebug() << "SixChanel Device:";
        qDebug() << "Address:" << address;
        qDebug() << "Type:" << type;
        qDebug() << "Flag:" << flag;
        qDebug() << "Version FW:" << versionFW;
        qDebug() << "Date:" << day << "/" << month << "/" << year;
        qDebug() << "BR:" << BR;
    }
} SixChanel_t;


class Serial: public QObject
{
    Q_OBJECT
public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;


    };

    enum  DeviceType{
         UnknownDevice,
         OneChanelDevice,
         SixChanelDevice
     };


    explicit Serial(QObject  *parent = nullptr);
    ~Serial();

    Settings settings() const;
void readPorlList();

QStringList getSerialPort();

void processBuffer();
signals:
    void dataReceived(const QString &data);
    void dataSent(const QString &data);
    void errorOccurred(const QString &error);
    // ... другие сигналы
        void oneChanelDataReceived(const OneChanel_t &data);
        void sixChanelDataReceived(const SixChanel_t &data);

public slots:
bool sendData(const QString &data);
bool sendData(QByteArray *data);
void readData();
bool openPort(int index, qint32 baudRate);
void closePort();


private:


    void baseSetting();


    Settings m_currentSettings;
//    QIntValidator *m_intValidator = nullptr;
    QStringList comPortsList;
    QSerialPort serial;

    // ... другие поля
        DeviceType m_currentDeviceType;
        SixChanel_t m_sixChanelData;
        int m_channelsReceived;

        DeviceType identifyDevice(const QString &data);
        bool parseOneChanelData(const QString &data);
        bool parseSixChanelData(const QString &data, int channelIndex);
};

#endif // SERIAL_H
