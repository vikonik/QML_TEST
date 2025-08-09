#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


//#include "buttonhandler.h"
#include "debug.h"
#include "mainlogick.h"
//#include "comboBoxModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
QApplication  app(argc, argv);

    QQmlApplicationEngine engine;

    MainLogick mainLogick;
    engine.rootContext()->setContextProperty("mainLogick", &mainLogick);
    engine.rootContext()->setContextProperty("comboBoxModel", mainLogick.getComboBoxModel());
    engine.rootContext()->setContextProperty("buttonHandler", mainLogick.getButtonHandler());
    engine.rootContext()->setContextProperty("tableModel", mainLogick.getTableModel());

// Загрузка QML
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




    return app.exec();
}
