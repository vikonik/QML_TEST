#include <QApplication>
#include <QString>
#include "debug.h"
#include "ui_debug.h"

#include <QDebug>
Debug::Debug(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debug)
{
    ui->setupUi(this);
    qDebug() << "Debug ready";
    log(QString("Готов"));

}

Debug::~Debug()
{
    delete ui;
}

void Debug::log(const QString &log){
    ui->plainTextEdit_log->appendPlainText(log);

}
