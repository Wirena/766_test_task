#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QString>
#include <memory>
#include <QUdpSocket>
#include <QNetworkDatagram>

class Chat : public QObject
{
    Q_OBJECT
    std::unique_ptr<QUdpSocket> socket = nullptr;
    int remotePort = -1;
    QString remotePortStr;
public:
    explicit Chat(QObject *parent = nullptr) : QObject(parent){}

private slots:
    void readPendingDatagrams();

public slots:
    void sendMessage(QString Msg);
    void setListenPort(QString Port);
    void setRemotePort(QString Port);
    void disconnect();
signals:
    void error(QString Err);
    void messageReceived(QString Msg);
};

#endif // CHAT_H
