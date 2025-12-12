#include "materiel.h"

Materiel::Materiel(QObject *parent)
    : QObject(parent)
{
    //Initialisation
    for (int i = 0; i < distancesLidar.size();i++)
    {
        distancesLidar[i]=0;
    }
}
