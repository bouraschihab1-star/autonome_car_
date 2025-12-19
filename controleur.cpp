#include "controleur.h"
#include <QDebug>
#include <QtMath>

Controleur::Controleur(Vehicule *_voiture)
    : voiture{_voiture}
{
    tictoc.setInterval(100);
    connect(&tictoc,&QTimer::timeout,
            this,&Controleur::process);
    tictoc.start();
}

void Controleur::process()
{
    // tableau des valeurs du lidar pour indice entre 0 et 180 (-> -90° à 90°)
    double wr;
    const int methode=2;
    if (methode==1)
    {
        wr=(double)(voiture->getDistance().at(180+30)-900)*0.01;//voiture.getDistance().at(180))*0.01;

    }
    else if (methode==2)
    {
        double mean=0;
        for (int i=-90;i<=90;i++)
        {
            mean+=voiture->getDistance().at(i+180)*qSin(qDegreesToRadians((double)i));
        }
        wr=mean*0.0001;
    }

}
