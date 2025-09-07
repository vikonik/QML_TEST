#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QByteArray>
#include <algorithm>
#include "dataStruct.h"

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

public slots:
    void setOneChanelDevices(const QVector<OneChanel_t> &devices);
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
