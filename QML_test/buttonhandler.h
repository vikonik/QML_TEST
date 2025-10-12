#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QDebug>
#include "tablecontroller.h"

class ButtonHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString groupMovingValue READ groupMovingValue WRITE setGroupMovingValue NOTIFY groupMovingValueChanged)

public:
    explicit ButtonHandler(QObject *parent = nullptr);

    void setTableController(TableController *controller);
signals:
    void buttonClicked(const QString &buttonName);  // Сигнал, который будет отправляться
    void signalSkanID();
    void signalConnect();
    void signalDisconnect();
    void signalReadRequest(const QString &serialID);
    void signalProgramRequest(const QString &deviceData);  // Измененный сигнал с QString
    void signalLoadFromFile(const QString &filePath);  // Новый сигнал для загрузки из файла
    void signalSendData(const QByteArray &data);
    void groupMovingValueChanged();

public slots:
    void onButtonClicked(const QString &buttonId);
    void print();
    void loadFromFileDialog();  // Новый слот для вызова диалога
    Q_INVOKABLE bool loadDataFromFile(const QString &filePath);


    QString groupMovingValue() const;
    void setGroupMovingValue(const QString &value);

private:
    TableController* m_tableController;
    QString m_groupMovingValue;

    void handleReadButton();
    void handleProgramButton();
    void handleDefaultSetupButton();//
    void handleDonloadSetupButton();
    void handleCopyButton();
    void handlePasteButton();
     //Управление одним контроллером
    void handlebuttonsBlindsControlbutton_UP();
    void handlebuttonsBlindsControlbutton_UpLeft();
    void handlebuttonsBlindsControlbutton_Stop();
    void handlebuttonsBlindsControlbutton_Down();
    void handlebuttonsBlindsControlbutton_DownRight();

     //Управление всеми контроллерами
    void handlebuttonsBlindsControlAllbutton_UP();
    void handlebuttonsBlindsControlAllbutton_UpLeft();
    void handlebuttonsBlindsControlAllbutton_Stop();
    void handlebuttonsBlindsControlAllbutton_Down();
    void handlebuttonsBlindsControlAllbutton_DownRight();

    //Управление группой контроллеров
    void handlebuttonGroupUp();
    void handlebuttonGroupDown();
    void handlebuttonGroupUpLeft();
    void handlebuttonGroupDownRight();

    QString serializeOneChannelData() const;  // Сериализация 1-канального устройства
    QString serializeSixChannelData() const;  // Сериализация 6-канального устройства
 //   bool loadDataFromFile(const QString &filePath);
    bool parseOneChannelLine(const QString &line, OneChanel_t &device);
    bool parseSixChannelLine(const QString &line, SixChanel_t &device);

};

#endif // BUTTONHANDLER_H
