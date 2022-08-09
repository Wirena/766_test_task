#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QString>
#include "chat.h"
#include <QString>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Chat chat;
    QThread thread;
    QShortcut shortcut;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onSendClick();
    void onConnectClick();
    void onDisconnectClick();
    void onError(QString Err);
    void onMessageReceive(QString);
signals:
    void sendMessage(QString);
    void setListenPort(QString);
    void setRemotePort(QString);
    void disconnect();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
