#ifndef MAINLOGICK_H
#define MAINLOGICK_H

#include <QObject>
#include "debug.h"
#include "serial.h"
#include "fifo.h"
#include "rfmax.h"
#include "comboboxmodel.h"
#include "buttonhandler.h"
#include "tablemodel.h"
#include "dataparser.h"


class MainLogick: public QObject {
    Q_OBJECT

public:
    explicit MainLogick(QObject *parent = nullptr);
    ~MainLogick();


    Debug *debugWindow;
    ButtonHandler* getButtonHandler() { return buttonHandler; }  // Геттер для ButtonHandler

    // Добавляем методы для работы с COM-портами
    Q_INVOKABLE void refreshComPorts(); // Обновление списка портов
    ComboBoxModel* getComboBoxModel() { return &comboBoxModel; } // Геттер для модели
    TableModel* getTableModel() { return tableModel; } // Геттер для модели

signals:
    void signalSendData(QByteArray *data);
//    void signalSendData(QString *data);
        void portsUpdated(); // Сигнал об обновлении списка портов

public slots:
    void scanNet();
    void detectDeviceType(QByteArray *data);
    //    void onPortSelected(int index); // Обработчик выбора порта
    void openPort();//Фасад для функции окрытияи порта

private:

    #define CH_1    "A"
    #define CH_6    "B"
    #define RFMAX   "W"
    #define IRMAX   "R"

    FIFO<2048> fifo;
    Serial *serial;
    RFMax *rfMax;
    QString deviceType;//последий определеннфый тип
    ComboBoxModel comboBoxModel; // Модель для комбобокса
    QString currentPort; // Текущий выбранный порт
    ButtonHandler *buttonHandler;  // ButtonHandler как член класса
TableModel *tableModel;
DataParser *parser;

    void setConnect();
    void setupSerial(); // Настройка последовательного порта

};

#endif // MAINLOGICK_H
