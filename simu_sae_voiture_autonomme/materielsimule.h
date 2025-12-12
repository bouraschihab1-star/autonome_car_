#ifndef MATERIELSIMULE_H
#define MATERIELSIMULE_H

#include "materiel.h"
//#include "suivrebord.h"
#include "tcpclient.h"


class MaterielSimule : public Materiel
{
public:
    MaterielSimule(int _numPort);// port de la voiture simuler

    TcpClient tcp; //TCP Client
    int numPort;



public slots:
    void deplacer(double vitesse, double angle) override;
    void processTcpDatas(QString data);
};

#endif // MATERIELSIMULE_H
