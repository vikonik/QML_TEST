#include "dataparser.h"
#include <QDebug>

#define ONE_CHANEL_DATA_LEN 50
// Реализация операторов сравнения
bool Chanel_t::operator<(const Chanel_t &other) const {
    return address.toInt() < other.address.toInt();
}

bool SixChanel_t::operator<(const SixChanel_t &other) const {
    return address.toInt() < other.address.toInt();
}

bool OneChanel_t::operator<(const OneChanel_t &other) const {
    return address.toInt() < other.address.toInt();
}

// Реализация методов для Chanel_t
bool Chanel_t::parseFromString(const QString &data) {
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

// Реализация методов для SixChanel_t
bool SixChanel_t::parseHeaderFromString(const QString &data) {
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

void SixChanel_t::debugPrint() const {
    qDebug() << "SixChanel Device:";
    qDebug() << "Address:" << address;
    qDebug() << "Type:" << type;
    qDebug() << "Flag:" << flag;
    qDebug() << "Version FW:" << versionFW;
    qDebug() << "Date:" << day << "/" << month << "/" << year;
    qDebug() << "BR:" << BR;
}

// Реализация методов для OneChanel_t
bool OneChanel_t::parseFromString(const QString &data) {
    if (data.length() != ONE_CHANEL_DATA_LEN) return false;

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
    tiltAngle = data.mid(pos, 2); pos += 2;
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

void OneChanel_t::debugPrint() const {
    qDebug() << "OneChanel Device:";
    qDebug() << "Address:" << address;
    qDebug() << "Type:" << type;
    qDebug() << "Flag:" << flag;
    qDebug() << "Version FW:" << versionFW;
    qDebug() << "Groups:" << group_1 << group_2 << group_3 << group_4;
    qDebug() << "Steps:" << steps << "EndAngle:" << tiltAngle;
    qDebug() << "Hight:" << hight << "TiltOnly:" << tiltOnly;
    qDebug() << "SAR:" << SAR << "CurrentPos:" << currentPosition;
    qDebug() << "Error:" << error << "Voltage:" << voltage;
    qDebug() << "Date:" << day << "/" << month << "/" << year;
    qDebug() << "BR:" << BR << "Dir:" << dir;
}

// Реализация методов DataParser
DataParser::DataParser(QObject *parent) : QObject(parent),
    m_currentDeviceType(UnknownDevice),
    m_channelsReceived(0)
{
}

DataParser::DeviceType DataParser::identifyDevice(const QString &data) {
    if (data.length() == ONE_CHANEL_DATA_LEN /*&& data.startsWith("0000")*/&& data.at(4) == 'A') {
        return OneChanelDevice;
    }
    else if (data.length() == 16 /*&& data.startsWith("0000") */&& data.at(4) == 'B') {
        return SixChanelDevice;
    }
    return UnknownDevice;
}

void DataParser::processRawData(const QByteArray &data) {
    m_buffer.append(data);
    //qDebug() << "Добавлено данных в буфер:" << data.size() << "байт";
    //qDebug() << "Текущий размер буфера:" << m_buffer.size() << "байт";
    processBuffer();
}

void DataParser::processBuffer() {
    while (true) {
        int startIndex = m_buffer.indexOf("\x0D\x0A");
        if (startIndex == -1) break;

        int endIndex = m_buffer.indexOf('\x3C', startIndex + 3);
        if (endIndex == -1) break;

        QByteArray block = m_buffer.mid(startIndex + 3, endIndex - startIndex - 3);
        QString dataString = QString::fromLatin1(block);

        qDebug() << "Извлечено сообщение:" << dataString;
        emit messageReceived(dataString);

        // Определяем тип устройства
        if (m_currentDeviceType == UnknownDevice) {
            m_currentDeviceType = identifyDevice(dataString);
            qDebug() << "Определен тип устройства:" << m_currentDeviceType;
        }

        // Обрабатываем данные в зависимости от типа устройства
        if (m_currentDeviceType == OneChanelDevice) {
            OneChanel_t deviceData;
            if (deviceData.parseFromString(dataString)) {
                deviceData.debugPrint();

                // Обновляем массив одноканальных устройств
                bool found = false;
                for (int i = 0; i < m_oneChanelDevices.size(); ++i) {
                    if (m_oneChanelDevices[i].address == deviceData.address) {
                        m_oneChanelDevices[i] = deviceData;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    m_oneChanelDevices.append(deviceData);
                }

                // Сортируем и отправляем сигнал
                updateDeviceArrays();
                emit oneChanelDataReceived(deviceData);
                m_currentDeviceType = UnknownDevice;
            } else {
                qDebug() << "Ошибка парсинга данных одноканального устройства";
            }
        }
        else if (m_currentDeviceType == SixChanelDevice) {
            if (/*dataString.startsWith("0000") && */dataString.length() == 16 && dataString.at(4) == 'B') {
                // Это заголовок шестиканального устройства
                if (m_currentSixChanelData.parseHeaderFromString(dataString)) {
                    m_currentSixChanelData.debugPrint();
                    m_channelsReceived = 0;
                }
            }
            else if (dataString.length() == 36) {
                // Это данные канала
                if (m_channelsReceived < 6) {
                    Chanel_t channelData;
                    if (channelData.parseFromString(dataString)) {
                        // Сохраняем данные канала
                        switch (m_channelsReceived) {
                            case 0: m_currentSixChanelData.chanel_1 = channelData; break;
                            case 1: m_currentSixChanelData.chanel_2 = channelData; break;
                            case 2: m_currentSixChanelData.chanel_3 = channelData; break;
                            case 3: m_currentSixChanelData.chanel_4 = channelData; break;
                            case 4: m_currentSixChanelData.chanel_5 = channelData; break;
                            case 5: m_currentSixChanelData.chanel_6 = channelData; break;
                        }
                        m_channelsReceived++;

                        qDebug() << "Получен канал" << m_channelsReceived << "из 6";

                        // Если получили все 6 каналов, обновляем массив
                        if (m_channelsReceived == 6) {
                            // Обновляем массив шестиканальных устройств
                            bool found = false;
                            for (int i = 0; i < m_sixChanelDevices.size(); ++i) {
                                if (m_sixChanelDevices[i].address == m_currentSixChanelData.address) {
                                    m_sixChanelDevices[i] = m_currentSixChanelData;
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                m_sixChanelDevices.append(m_currentSixChanelData);
                            }

                            // Сортируем и отправляем сигнал
                            updateDeviceArrays();
                            emit sixChanelDataReceived(m_currentSixChanelData);
                            m_currentDeviceType = UnknownDevice;
                        }
                    }
                }
            }
        }

        m_buffer.remove(0, endIndex + 1);
    }

    if (m_buffer.size() > 1024) {
        qDebug() << "Буфер слишком большой, очистка";
        m_buffer.clear();
        m_currentDeviceType = UnknownDevice;
        m_channelsReceived = 0;
    }
}

void DataParser::updateDeviceArrays() {
    // Сортируем массивы устройств по адресу
    std::sort(m_oneChanelDevices.begin(), m_oneChanelDevices.end());
    std::sort(m_sixChanelDevices.begin(), m_sixChanelDevices.end());

    // Отправляем сигнал об обновлении
    emit devicesUpdated();

//    qDebug() << "Массивы устройств обновлены и отсортированы";
//    qDebug() << "Одноканальных устройств:" << m_oneChanelDevices.size();
//    qDebug() << "Шестиканальных устройств:" << m_sixChanelDevices.size();
}

QVector<OneChanel_t> DataParser::getOneChanelDevices() const {
    return m_oneChanelDevices;
}

QVector<SixChanel_t> DataParser::getSixChanelDevices() const {
    return m_sixChanelDevices;
}

void DataParser::resetParserState() {
    m_currentDeviceType = UnknownDevice;
    m_channelsReceived = 0;
    m_buffer.clear();
    qDebug() << "Состояние парсера сброшено";
}
