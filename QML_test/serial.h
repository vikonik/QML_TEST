#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
//#include <QDialog>
#include <QSerialPort>

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
void readPorlList();

QStringList getSerialPort();

signals:
    void dataReceived(const QString &data);
    void dataSent(const QString &data);
    void errorOccurred(const QString &error);

public slots:
bool sendData(const QString &data);
bool sendData(const QByteArray &data);
void readData();
private:


    void baseSetting();
    bool openPort(int index, qint32 baudRate);
    void closePort();

    Settings m_currentSettings;
//    QIntValidator *m_intValidator = nullptr;
    QStringList comPortsList;
    QSerialPort serial;
};

#endif // SERIAL_H
