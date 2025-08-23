#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QByteArray>
#include <algorithm>

// Предварительное объявление структур
struct Chanel_t;
struct SixChanel_t;
struct OneChanel_t;

// Структура для канала
struct Chanel_t {
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

    bool parseFromString(const QString &data);
    bool operator<(const Chanel_t &other) const;
};

// Структура для шестиканального устройства
struct SixChanel_t {
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

    bool parseHeaderFromString(const QString &data);
    bool operator<(const SixChanel_t &other) const;
    void debugPrint() const;
};

// Структура для одноканального устройства
struct OneChanel_t {
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

    bool parseFromString(const QString &data);
    bool operator<(const OneChanel_t &other) const;
    void debugPrint() const;
};

class DataParser : public QObject
{
    Q_OBJECT
public:
    enum DeviceType {
        UnknownDevice,
        OneChanelDevice,
        SixChanelDevice
    };

    explicit DataParser(QObject *parent = nullptr);

    // Метод для обработки сырых данных
    void processRawData(const QByteArray &data);

    // Методы для доступа к массивам устройств
    QVector<OneChanel_t> getOneChanelDevices() const;
    QVector<SixChanel_t> getSixChanelDevices() const;

    // Сброс состояния парсера
    void resetParserState();

signals:
    void oneChanelDataReceived(const OneChanel_t &data);
    void sixChanelDataReceived(const SixChanel_t &data);
    void devicesUpdated();
    void messageReceived(const QString &message);  // Сигнал о полученном сообщении

private:
    void processBuffer();
    DeviceType identifyDevice(const QString &data);
    void updateDeviceArrays();

    // Текущее состояние парсера
    DeviceType m_currentDeviceType;
    SixChanel_t m_currentSixChanelData;
    int m_channelsReceived;

    // Буфер для накопления данных
    QByteArray m_buffer;

    // Массивы для хранения устройств
    QVector<OneChanel_t> m_oneChanelDevices;
    QVector<SixChanel_t> m_sixChanelDevices;
};

#endif // DATAPARSER_H
