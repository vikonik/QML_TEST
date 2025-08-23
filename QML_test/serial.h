#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>

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

    explicit Serial(QObject  *parent = nullptr);
    ~Serial();

    Settings settings() const;
    void readPortList();
    QStringList getSerialPort();

signals:
    void dataReceived(const QByteArray &data);  // Изменено: передаем сырые данные
    void dataSent(const QString &data);
    void errorOccurred(const QString &error);
    void rawDataReceived(const QByteArray &data);  // Новый сигнал для сырых данных

public slots:
    bool sendData(const QString &data);
    bool sendData(const QByteArray &data);
    void readData();
    bool openPort(int index, qint32 baudRate);
    void closePort();

    void readPorlList();
private:
    Settings m_currentSettings;
    QStringList comPortsList;
    QSerialPort serial;
};

#endif // SERIAL_H
