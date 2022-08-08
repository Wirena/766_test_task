#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QString>
#include "chat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool listening = false;
    bool connected = false;
    Chat chat;
    QThread thread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onSendClick();
    void onConnectClick();
    void onAttachClick();
    void onListenClick();
    void onError(QString Err);
    void onMessageReceive(QString);
signals:
    void sendMessage(QString);
    void setListenPort(QString);
    void setRemotePort(QString);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
