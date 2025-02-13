#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "buttonhandler.h"
#include "debug.h"
#include "mainlogick.h"
#include "comboBoxModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
QApplication  app(argc, argv);

    QQmlApplicationEngine engine;

    ButtonHandler buttonHandler;
    engine.rootContext()->setContextProperty("buttonHandler", &buttonHandler);

    /* пример подключения кнопки для взаимодействия с кодом
     * в AnotherHandlerсоздаем слот для взаимодействия
    AnotherHandler anotherHandler;         // Создаем объект AnotherHandler

    // Подключаем сигнал из ButtonHandler к слоту в AnotherHandler
    QObject::connect(&buttonHandler, &ButtonHandler::buttonClicked,
                     &anotherHandler, &AnotherHandler::handleButtonClicked);
    */

    // Создаём экземпляр модели
    ComboBoxModel comboBoxModel;
    comboBoxModel.setItems({"Apple", "Banana", "Cherry"}); // Начальные данные
    // Делаем модель доступной в QML
    engine.rootContext()->setContextProperty("comboBoxModel", &comboBoxModel);


    engine.addImportPath(":/");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

// debugWindow = new Debug();
//    debugWindow.show();
    MainLogick mainLogick;



    return app.exec();
}
