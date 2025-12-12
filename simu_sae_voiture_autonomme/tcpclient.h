#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QTimer>
#include <QObject>
#include <QDataStream>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QString _addr
                       ,int _port,QObject *parent = nullptr);

    void sendDatas(QString datas);
private:
    bool isconnect;
    QString addr;
    int port;
    QTcpSocket clientSocket;
    QTimer monTimer;
    QDataStream dataIn;
    QString datas;
    void getvalue();
private slots:
    void onConnected();
    void reConnected();
    void Deco();
signals:
    void newDatas(QString datas);

};

#endif // TCPCLIENT_H

