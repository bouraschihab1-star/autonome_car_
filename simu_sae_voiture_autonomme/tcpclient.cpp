#include "tcpclient.h"
#include <QTcpSocket>
#include <QObject>


TcpClient::TcpClient(QString _addr
                     , int _port, QObject *parent)
    : QObject{parent}

{
    addr = _addr;
    port = _port;
    monTimer.setInterval(100);
    monTimer.start();
    isconnect = false;

    connect(&monTimer,&QTimer::timeout
            ,this,&TcpClient::reConnected);

    connect(&clientSocket, &QTcpSocket::disconnected,
            this, &TcpClient::Deco);

    connect(&clientSocket, &QTcpSocket::connected,
            this, &TcpClient::onConnected);

    connect(&clientSocket, &QTcpSocket::readyRead,
            this, &TcpClient::getvalue);


    dataIn.setDevice(&clientSocket);
}

void TcpClient::onConnected()
{
    qDebug() << "connexion établie";
                monTimer.stop();
    isconnect = true;


}

void TcpClient::reConnected()
{
    clientSocket.connectToHost(addr,port);
    qDebug() << "tentative de connexion";
}

void TcpClient::Deco()
{
    qDebug() << "Déconnecté";
    monTimer.start();
    isconnect = false;


}
void TcpClient::getvalue()
{
    dataIn.startTransaction();
    if (!dataIn.commitTransaction()) return;
    dataIn >> datas;
    emit newDatas(datas);
}

void TcpClient::sendDatas(QString datas1)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << datas1;
    qDebug()<< "message envoyé :" << datas1;
    clientSocket.write(block);
}




