#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), shortcut(this)
{
    ui->setupUi(this);

    ui->remotePortEdit->setValidator(new QIntValidator(0, 65536, ui->remotePortEdit));
    ui->localPortEdit->setValidator(new QIntValidator(0, 65536, ui->localPortEdit));
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendClick);
    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClick);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &MainWindow::onDisconnectClick);
    shortcut.setKey(Qt::CTRL | Qt::Key_Return);
    connect(&shortcut, &QShortcut::activated, this, &MainWindow::onSendClick);
    shortcut.setEnabled(true);
    shortcut.setContext(Qt::ApplicationShortcut);
    chat.moveToThread(&thread);
    connect(this, &MainWindow::sendMessage, &chat, &Chat::sendMessage);
    connect(&chat, &Chat::error, this, &MainWindow::onError);
    connect(&chat, &Chat::messageReceived, this, &MainWindow::onMessageReceive);
    connect(this, &MainWindow::setRemotePort, &chat, &Chat::setRemotePort);
    connect(this, &MainWindow::setListenPort, &chat, &Chat::setListenPort);
    connect(this, &MainWindow::disconnect, &chat, &Chat::disconnect);
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
    const auto message = ui->messageText->toPlainText().trimmed();
    if(!message.isEmpty()){
        QString chatMessage{"you: "};
        chatMessage.append(message);
        ui->chatTextWidget->append(chatMessage);
        ui->messageText->document()->clear();
        emit sendMessage(message);
    }
}

void MainWindow::onConnectClick()
{
    const auto remotePort = ui->remotePortEdit->text();
    emit setRemotePort(remotePort);

    const auto localPort = ui->localPortEdit->text();
    if(!localPort.isEmpty())
        emit setListenPort(localPort);
    ui->localPortEdit->setEnabled(false);
    ui->remotePortEdit->setEnabled(false);

}

void MainWindow::onDisconnectClick()
{
    ui->localPortEdit->setEnabled(true);
    ui->remotePortEdit->setEnabled(true);
    emit disconnect();
}

void MainWindow::onError(QString Err)
{
    QMessageBox messageBox(QMessageBox::Icon::Warning, "Error", Err, QMessageBox::StandardButton::Ok, this);
    messageBox.exec();
}

void MainWindow::onMessageReceive(QString Msg)
{
    ui->chatTextWidget->append(Msg);
}


