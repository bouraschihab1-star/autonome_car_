#ifndef COMMUNICATIONTCP_H
#define COMMUNICATIONTCP_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class CommunicationTCP : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationTCP(int _port,QObject *parent = nullptr);
    void setServoDirection(double *_servoDirection);

private :
    int port;
    QTcpServer monServeur;
    QTcpSocket *serveurSocket=nullptr;
    QDataStream dataIn;

    QStringList messageInListe;

    bool isConnected;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2;
public slots:
    void sendDatas(const QString &data);
    void reStartConnexion();

private slots:
    void newConnection();
    void closeConnection();
    void getDatas();

signals:
    void newValue(const QStringList &dataInListe);
    void connected();
    void disConnected();

};

#endif // COMMUNICATIONTCP_H

