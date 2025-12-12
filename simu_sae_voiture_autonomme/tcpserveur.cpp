#include "tcpserveur.h"
#include <QHostAddress>
#include <QDebug>

TcpServeur::TcpServeur(QObject *parent)
    : QObject(parent)
{
    monServeur.setParent(this);

    bool etat = monServeur.listen(QHostAddress(QHostAddress::AnyIPv4), 8883);;
    if (etat)
        qDebug() << "Listening...";
    else
        qWarning() << "Listen failed:" << monServeur.errorString();

    connect(&monServeur, &QTcpServer::newConnection,this, &TcpServeur::onNewConnection);
}

void TcpServeur::onNewConnection()

{
    clientSocket = monServeur.nextPendingConnection();
    qDebug() << "New client connected!";

    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServeur::onReadyRead);
    dataIn.setDevice(clientSocket);
    sendDatas(R"(Hello newbie!)");
}

void TcpServeur::onReadyRead()
{
    if (!clientSocket) return;
    dataIn.startTransaction();
    if (!dataIn.commitTransaction()) return;
    QString datas;
    while (dataIn.atEnd()==false)
    {
        dataIn >> datas;
        qDebug() << "Received data: "<<datas;
    }
    emit newDatas(datas); //envoye le signal avec datas pour autre classe, si besoin
}


void TcpServeur::sendDatas(QString datas)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << datas;
    // qDebug()<<"message envoyé :"<<val;
    clientSocket->write(block);
}
