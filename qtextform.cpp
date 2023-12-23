#include "qtextform.h"
#include "ui_qtextform.h"
#include <QWidget>
#include <QPlainTextEdit>
#include <QFile>
#include <QObject>
#include <QInputDialog>


qtextform::qtextform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::qtextform)
{
    ui->setupUi(this);
}

qtextform::~qtextform()
{
    delete ui;
}

void qtextform::loadFromFile(QPlainTextEdit* child, QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        //alert that file did not open
        qDebug() << "An error has occured, file did not open!";
        return;
    }
    QString wholeFile = file.readAll();
    file.close();
    child->insertPlainText(wholeFile);

}

QString qtextform::saveToFile(QPlainTextEdit* child, QString fileName){
    qDebug() << "At start of saveToFile fileName is: " << fileName;
    QString data = child->toPlainText();
    int newFile = 0;
    if(!fileName.compare("./")){
    bool ok;
    fileName.append(QInputDialog::getText(child, tr("New File Name"),
                                          tr("New File Name:"), QLineEdit::Normal,
                                          " ", &ok));
    newFile = 1;
    fileName.append(".txt");
    }
    QFile file(fileName);

    file.open(QIODeviceBase::ReadWrite);
    if(!file.isOpen())
    {
        //alert that file did not open
        qDebug() << "An error has occured, file did not open!";
        return "1";
    }
    QTextStream outStream(&file);
    if(!data.compare("")){
        outStream << " ";

    }
    outStream << data;
    file.close();
    return fileName;
}
//method to pop
void qtextform::undoChange(QPlainTextEdit* child){
    QString data = child->toPlainText();

}



