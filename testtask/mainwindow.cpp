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
    chat.moveToThread(&thread);
    connect(&thread, &QThread::started, &chat, &Chat::start);
    connect(&thread, &QThread::finished, &chat, &Chat::finish);
    connect(this, &MainWindow::sendMessage, &chat, &Chat::sendMessage);
    connect(&chat, &Chat::error, this, &MainWindow::onError);
    connect(&chat, &Chat::messageReceived, this, &MainWindow::onMessageReceive);
    connect(this, &MainWindow::setRemotePort,&chat, &Chat::setRemotePort);
    connect(this, &MainWindow::setListenPort ,&chat, &Chat::setListenPort);
    thread.start();
}

MainWindow::~MainWindow()
{
    thread.exit();
    thread.wait(1000);
    delete ui;
}


void MainWindow::onSendClick()
{
    const auto message = ui->messageText->toPlainText();
    if(!message.isEmpty()){
        QString chatMessage{"you: "};
        chatMessage.append(message);
        ui->chatTextWidget->append(chatMessage);
        emit sendMessage(message);
    }
}

void MainWindow::onConnectClick()
{
    const auto port = ui->remotePortEdit->text();
      emit setRemotePort(port);
}

void MainWindow::onAttachClick()
{

}

void MainWindow::onListenClick()
{
    const auto port = ui->localPortEdit->text();
        emit setListenPort(port);
}

void MainWindow::onError(QString Err)
{
    QMessageBox messageBox(QMessageBox::Icon::Warning, "Error", Err, QMessageBox::StandardButton::Ok,this);
    messageBox.exec();
}

void MainWindow::onMessageReceive(QString Msg)
{
    ui->chatTextWidget->append(Msg);
}

