#include "vehiculethread.h"


VehiculeThread::VehiculeThread(int _posX, int _posY, int _port, Circuit &_circuit)
    : port(_port)
    , circuit(_circuit)
    ,posX(_posX)
    ,posY(_posY)
{

}

void VehiculeThread::run()
{
    voiture=new Vehicule(posX,posY,port,circuit);
    mutex.unlock();
    exec();
}
