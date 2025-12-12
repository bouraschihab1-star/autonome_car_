#ifndef TCPSERVEUR_H
#define TCPSERVEUR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class TcpServeur : public QObject
{
    Q_OBJECT
public:
    explicit TcpServeur(QObject *parent = nullptr);

    void sendDatas(QString datas);

signals:
    void newDatas(QString datas);

private slots:
    void onNewConnection();
    void onReadyRead();

private:

    QTcpServer  monServeur;
    QTcpSocket *clientSocket = nullptr;
    QDataStream dataIn;
};

#endif // TCPSERVEUR_H
