#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qtextform.h"
#include <QTabWidget>
#include <QTextStream>
#include <QInputDialog>
#include <QFileDialog>
#include <QWidget>
#include <QPushButton>
#include <QFileSystemModel>
#include <QTreeView>
#include <QSplitter>
#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <QList>
#include <QShortcut>
#include <QShortcutEvent>
#include <QStack>

QString currFilePath;
QList<QString> filePaths;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //account for first two default tabs it wont let me close from code
    filePaths.push_back("./");
    filePaths.push_back("./");
    currFilePath = "./";
    ui->setupUi(this);
    //set up new tab button
    QWidget* pTabCornerWidget = new QWidget(this);
    QPushButton* pButton = new QPushButton(pTabCornerWidget);
    pButton->setText("+");
    pButton->setMaximumSize(QSize(50,50));
    QObject::connect(pButton, SIGNAL(clicked()), this, SLOT(on_pTabCornerWidget_triggered()));
    QHBoxLayout* pHLayout = new QHBoxLayout(pTabCornerWidget);
    pHLayout->addWidget(pButton);
    pHLayout->setContentsMargins(0, 0, 0, 0);
    ui->tabWidget -> setCornerWidget(pTabCornerWidget, Qt::TopRightCorner);

    QShortcut *saveShortcut = new QShortcut(QKeySequence(tr("ctrl+s", "File|Save")), this);
    QObject::connect(saveShortcut, &QShortcut::activated, this, &MainWindow::on_saveShortcut_activated);

    QShortcut *newTabShortcut = new QShortcut(QKeySequence(tr("ctrl+n", "File|New")), this);
    QObject::connect(newTabShortcut, &QShortcut::activated, this, &MainWindow::on_newShortcut_activated);

    QShortcut *openFileShortcut = new QShortcut(QKeySequence(tr("ctrl+o", "File|Open")), this);
    QObject::connect(openFileShortcut, &QShortcut::activated, this, &MainWindow::on_openFileShortcut_activated);

    QShortcut *undoChangeShortcut = new QShortcut(QKeySequence(tr("ctrl+o", "File|Open")), this);
    QObject::connect(openFileShortcut, &QShortcut::activated, this, &MainWindow::on_undoChangeShortcut_activated);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
    ui->tabWidget->setCurrentIndex((index));
    filePaths.removeAt(index);
}

void MainWindow::on_pTabCornerWidget_triggered(){

    ui->tabWidget->addTab(new qtextform, QString("Tab %0").arg(ui->tabWidget->count() + 1));
    currFilePath = "./";
    //TODO push file path into vector
    filePaths.push_back(currFilePath);

}

void MainWindow::on_actionNew_triggered()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("New File Name:"), QLineEdit::Normal,
                                             " ", &ok);

    fileName = fileName.append(".txt");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << " ";
    file.close();
    ui->tabWidget->addTab(new  qtextform, QString("Tab %0").arg(ui->tabWidget->count() + 1));
    currFilePath = "./";
    currFilePath.append(fileName);
    filePaths.push_back(currFilePath);
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Text Files (*.txt)"));
    if(fileName.compare("")){

    //load text into buffer string
    int index =  ui->tabWidget->addTab(new  qtextform, QString("Tab %0").arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(index);
    QWidget *tab = ui->tabWidget->widget(index);
    QPlainTextEdit *textBox = tab->findChild<QPlainTextEdit*>();
    qtextform::loadFromFile(textBox, fileName);
    currFilePath = fileName;
    filePaths.push_back(fileName);
    }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{

    //TODO On click, change global path to local path
    currFilePath = filePaths.at((qsizetype) index);
}


void MainWindow::on_actionSave_triggered()
{
    //get UI Widget and get it's plainTextBox
    int index =  ui->tabWidget->currentIndex();
    QWidget *tab = ui->tabWidget->widget(index);
    QPlainTextEdit *textBox = tab->findChild<QPlainTextEdit*>();
    //save file
    QString verifier = qtextform::saveToFile(textBox, filePaths.at(index));
    if(!verifier.compare("1")){
        qDebug() << "An error occurred";
    }
    else{
        filePaths.replace(index, verifier);
    }
}

void MainWindow::on_saveShortcut_activated(){

    MainWindow::on_actionSave_triggered();

}

void MainWindow::on_newShortcut_activated(){
    MainWindow::on_pTabCornerWidget_triggered();
}

void MainWindow::on_openFileShortcut_activated(){

    MainWindow::on_actionOpen_triggered();

}




void MainWindow::on_actionSave_as_triggered()
{
    //get new file path from user
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Text Files (*.txt)"));

    //replace old file path
    int index =  ui->tabWidget->currentIndex();
    filePaths.replace(index, fileName);
    //set curr file path even though I probably dont need that variable
    currFilePath = fileName;


}
//call qtextform::undoChange on ctrl z
void MainWindow::on_undoChangeShortcut_activated()
{
    //get UI Widget and get it's plainTextBox
    int index =  ui->tabWidget->currentIndex();
    QWidget *tab = ui->tabWidget->widget(index);
    QPlainTextEdit *textBox = tab->findChild<QPlainTextEdit*>();
    qtextform::undoChange(textBox);

}





