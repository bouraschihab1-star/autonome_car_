#include "communicationtcp.h"
#include <QDebug>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

CommunicationTCP::CommunicationTCP(int _port, QObject *parent)
    : QObject{parent}
    , port(_port)
{
    isConnected=false;
    monServeur.listen(QHostAddress(QHostAddress::AnyIPv4),port);
    connect(&monServeur,&QTcpServer::newConnection,
            this,&CommunicationTCP::newConnection);
}


void CommunicationTCP::newConnection()
{
    if (serveurSocket!=nullptr)
    {
        qDebug()<<"2ème connection : pas pris en charge => déconnecte la 1ère";
        closeConnection();
    }
    qDebug()<<"nouvelle connection !";
    serveurSocket = monServeur.nextPendingConnection();
    connect(serveurSocket,&QTcpSocket::disconnected,
            this,&CommunicationTCP::closeConnection);
    connect(serveurSocket,&QTcpSocket::readyRead,
            this,&CommunicationTCP::getDatas);
    dataIn.setDevice(serveurSocket);
    isConnected=true;
    emit connected();
}

void CommunicationTCP::closeConnection()
{
    qDebug()<<"fermeture de la connection";
    disconnect(serveurSocket,&QTcpSocket::disconnected,
               this,&CommunicationTCP::closeConnection);
    disconnect(serveurSocket,&QTcpSocket::readyRead,
               this,&CommunicationTCP::getDatas);
    dataIn.setDevice(nullptr);
    serveurSocket->deleteLater();
    serveurSocket=nullptr;
    isConnected=false;
    emit disConnected();
}

void CommunicationTCP::sendDatas(const QString &data)
{
    if (isConnected)
    {
 //       t1 = high_resolution_clock::now();
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out<<data;
        serveurSocket->write(block);
    }
}

void CommunicationTCP::reStartConnexion()
{
    monServeur.close();
    serveurSocket->disconnect();
    closeConnection();
    monServeur.listen(QHostAddress(QHostAddress::AnyIPv4),port);
}

void CommunicationTCP::getDatas()
{
 //   t2 = high_resolution_clock::now();
    dataIn.startTransaction();
    if (!dataIn.commitTransaction()) return;
    QString message;
    while(dataIn.atEnd()==false)
    {
        dataIn >> message;
    }
    messageInListe.clear();
    messageInListe = message.split(';');
    if (messageInListe.size()==2)
    {
        emit newValue(messageInListe);
    }
//    auto diff = duration_cast<std::chrono::microseconds>(t2-t1);
//    qDebug()<<diff.count()<<messageInListe.size();
}
