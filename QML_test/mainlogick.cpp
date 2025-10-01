#include "mainlogick.h"
#include "debug.h"
#include "serial.h"
#include <QDebug>
#include<QString>
#include <QObject> // Это важно для работы с сигналами и слотами
#include "comboboxmodel.h"
#include "buttonhandler.h"

MainLogick::MainLogick(QObject *parent) : QObject(parent),
    comboBoxModel()
{
    qDebug() << "MainLogick initialization";

    // Инициализация компонентов
    rfMax = new RFMax();
    debugWindow = new Debug();
    serial = new Serial();
    tableModel = new TableModel();
    dataParser = new DataParser(this);
    tableController = new TableController(this);
    tableController->setModel(tableModel);
    tableController->setDataParser(dataParser); // Устанавливаем связь
    buttonHandler = new ButtonHandler();// Инициализируем ButtonHandler
    buttonHandler->setTableController(tableController);
    deviceType.clear();

    // Показываем окно отладки
    debugWindow->show();
    debugWindow->log("MainLogick initialized");

    // Инициализация модели начальными данными
    comboBoxModel.setItems({"Scanning ports..."});

    // Обновляем список COM-портов
    refreshComPorts();

    // Настраиваем соединения
    setConnect();


}

/**/
MainLogick::~MainLogick()
{
    delete rfMax;
    delete debugWindow;
    delete serial;
    delete buttonHandler;

}

/*
Настраиваем connect
*/
// В методе setConnect() замените соединения:
void MainLogick::setConnect(){
    connect(buttonHandler, &ButtonHandler::signalConnect, this, &MainLogick::openPort);
    connect(buttonHandler, &ButtonHandler::signalDisconnect, serial, &Serial::closePort);
    connect(buttonHandler, &ButtonHandler::signalSkanID,this, &MainLogick::scanNet);

    connect(this, &MainLogick::signalSendData,
            serial,
            static_cast<bool (Serial::*)(const QByteArray &)>(&Serial::sendData));

    connect(serial, &Serial::rawDataReceived, dataParser, &DataParser::processRawData);

    // Временно вернем старые соединения для отладки
//    connect(dataParser, &DataParser::devicesUpdated, this, [this](){
//        tableModel->loadOneChanelData(dataParser->getOneChanelDevices());
//        //tableModel->loadSixChanelData(dataParser->getSixChanelDevices());

//    });

    // Для отладки добавим соединения для шестиканальных устройств
    connect(dataParser, &DataParser::sixChanelDataReceived, this, [this](const SixChanel_t &data){
        // Пока просто логируем получение шестиканального устройства
        tableModel->loadSixChanelData(dataParser->getSixChanelDevices());
        qDebug() << "Received six channel device:" << data.address;
    });
    connect(dataParser, &DataParser::oneChanelDataReceived, this, [this](const OneChanel_t &data){
        // Пока просто логируем получение шестиканального устройства
        tableModel->loadOneChanelData(dataParser->getOneChanelDevices());
        qDebug() << "Received one channel device:" << data.address;
    });


    connect(buttonHandler, &ButtonHandler::signalReadRequest,
            this, &MainLogick::handleReadRequest);
}

/**/
void MainLogick::openPort(){
    qDebug() << "comboBoxModel.currentIndex() " + QString::number(comboBoxModel.currentIndex());
    serial->openPort(comboBoxModel.currentIndex(),19200);


}
/**/
void MainLogick::refreshComPorts()
{
    debugWindow->log("Refreshing COM ports...");
    serial->readPorlList();
    QStringList comPorts = serial->getSerialPort();

    // Обновляем модель
    if (!comPorts.isEmpty()) {
        comboBoxModel.setItems(comPorts);
        comboBoxModel.setCurrentIndex(0);
        QString logMsg = "Available COM ports: " + comPorts.join(", ");
        debugWindow->log(logMsg);
    } else {
        comboBoxModel.setItems({"No COM ports found"});
        debugWindow->log("No COM ports available!");
    }
}


/*
Отправляем запрос на сканирование сети
*/
void MainLogick::scanNet()
{
    debugWindow->log("Starting network scan...");
    QByteArray command = ">Scan?<";

    emit signalSendData(command);
}

/*
Определяем что за устройство
*/
void MainLogick::detectDeviceType(QByteArray *data){

    uint8_t tmp;
    //положили полученный данные а буфер
    for (char byte : *data) {
        if (!fifo.isFull()) {
            fifo.push(static_cast<uint8_t>(byte));
        } else {
            fifo.flush();
            break; // Останавливаемся, если FIFO заполнен
        }
    }

    //ищем начало команды
    QString marker = "\r\n>";
    QString compData;
    size_t n = 0;

    do{
        compData.append(fifo.getN(n));
        compData.append(fifo.getN(n+1));
        compData.append(fifo.getN(n+2));
        n++;

    } while(!!QString::compare(marker, compData) || fifo.count() < n );

    //Если не нашли начала, то это или продолжение пакета или не полные данные
    if(n >= fifo.count() && deviceType.isEmpty())
        return;
    //Ecли начало нашли
    if(n < fifo.count()){
        n -= 1;
        fifo.shiftTail(n);//переставили хвост на начало команды
        //определяем тип устройства
        deviceType.append(fifo.getN(7));// 7 - смещеие в массиве для чтения типа устройства

    }
    else if(!deviceType.isEmpty()){

        if(!QString::compare(deviceType, CH_1)){

        }
        else if(!QString::compare(deviceType, CH_6)){

        }
        else if(!QString::compare(deviceType, RFMAX)){
            if(!rfMax->detected){
                rfMax->currentAddr = 0;
                memset(rfMax->rfMax, 0, rfMax->getSizeRFMAX_Type());//Очистили структуру
                rfMax->detected = true;
            }
            while(!fifo.isEmpty()){
                uint8_t* basePtr = reinterpret_cast<uint8_t*>(&rfMax->rfMax);//получили удрес структуры
                basePtr[rfMax->currentAddr++] = fifo.front(); // Записываем байт в структуру
                fifo.pop();

            }

        }
        else if(!QString::compare(deviceType, IRMAX)){

        }
        else
            return;

    }
}

/**/
void MainLogick::getDeviceInfo(){

}

/**/
void MainLogick::handleReadRequest(const QString &serialId){
    debugWindow->log("Read from SerialID");
    QByteArray command;
    command.append(">");
    command.append(serialId);
    command.append("?<");
    emit signalSendData(command);

}
