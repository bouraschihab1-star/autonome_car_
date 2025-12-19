#ifndef VEHICULETHREAD_H
#define VEHICULETHREAD_H

#include <QObject>
#include <QThread>
#include "vehicule.h"
#include "circuit.h"
#include <QMutex>

class VehiculeThread : public QThread
{
public:
    VehiculeThread(int posX,int posY,int _port,Circuit &_circuit);
    QMutex mutex;
    void run() override ;
    Vehicule *voiture;
    int port;
    Circuit &circuit;
    int posX;
    int posY;
};

#endif // VEHICULETHREAD_H
