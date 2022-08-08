#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool listening = false;
    bool connected = false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onSendClick();
    void onConnectClick();
    void onAttachClick();
    void onListenClick();
    void onError(QString Err);
signals:
    //void sendMessage(QString);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
