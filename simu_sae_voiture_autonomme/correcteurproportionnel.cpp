#include "correcteurproportionnel.h"
#include <QDebug>

CorrecteurProportionnel::CorrecteurProportionnel(QObject *parent)
    : Correcteur{parent}
{

}



double CorrecteurProportionnel::process(double entree, double nouvelleConsigne)
{
   // qDebug() <<"valeur entrer"<< entree;
   double erreur = (nouvelleConsigne - entree);
    double resultat = kp* erreur;
    //qDebug() << resultat;
     if (resultat > 1.0)
     resultat = 1.0;
    else if (resultat < -1.0)
     resultat = -1.0;
   //  qDebug() << resultat;
    return resultat;

}
