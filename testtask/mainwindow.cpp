#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->remotePortEdit->setValidator(new QIntValidator(0, 65536, ui->remotePortEdit));
    ui->localPortEdit->setValidator(new QIntValidator(0, 65536, ui->localPortEdit));
    connect(ui->attachButton, &QPushButton::clicked, this, &MainWindow::onAttachClick);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendClick);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClick);
    connect(ui->listenButton, &QPushButton::clicked, this, &MainWindow::onListenClick);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onSendClick()
{


}

void MainWindow::onConnectClick()
{

}

void MainWindow::onAttachClick()
{

}

void MainWindow::onListenClick()
{

}

void MainWindow::onError(QString Err)
{
    QMessageBox messageBox(QMessageBox::Icon::Warning, "Error", Err, QMessageBox::StandardButton::Ok,this);
    messageBox.exec();
}


