#include "chat.h"
#include <QThread>
#include <QDebug>
#include <QHostAddress>



void Chat::readPendingDatagrams()
{
    while (socket->hasPendingDatagrams()) {
        const auto datagram = socket->receiveDatagram();
        if(datagram.senderPort()!=remotePort) continue;
        if(datagram.isNull()) continue;
        auto datagramString = QString::fromUtf8(datagram.data());
        if(datagramString.isEmpty()) continue;
        datagramString.prepend(remotePortStr+": ");
        emit messageReceived(datagramString);
    }
}

void Chat::sendMessage(QString Msg)
{
    if(!socket){
        emit error("Set Listen address before sending messages");
        return;
    }
    if(remotePort==-1){
        emit error("Set Remote address before sending messages");
        return;
    }
    const auto bytes = Msg.toUtf8();
    const auto bytesSend = socket->writeDatagram(bytes,QHostAddress::LocalHost, remotePort);
    if(bytesSend != bytes.size()){
        const auto err = socket->error();
        if(err == QUdpSocket::SocketError::DatagramTooLargeError)
            emit error("Message size is too big");
        else
            emit error("Failed to send message");
    }
}

void Chat::setListenPort(QString Port)
{
    bool intParsed = false;
    const auto port = Port.toInt(&intParsed);
    if(!intParsed){
        emit error("Failed to parse port number");
        return;
    }
    if(socket)
        socket->disconnect();
    socket = std::make_unique<QUdpSocket>(new QUdpSocket(this));
    if(!socket->bind(QHostAddress::LocalHost, port)){
        emit error("Failed to to bind");
        return;
    }
    connect(socket.get(), &QUdpSocket::readyRead, this, &Chat::readPendingDatagrams);
}

void Chat::setRemotePort(QString Port)
{
    bool intParsed = false;
    const auto port = Port.toInt(&intParsed);
    if(!intParsed){
        emit error("Failed to parse port number");
        return;
    }
    remotePortStr = Port;
    remotePort = port;
}

void Chat::disconnect()
{
    if(socket)
        socket->disconnect();
    socket = nullptr;
}
