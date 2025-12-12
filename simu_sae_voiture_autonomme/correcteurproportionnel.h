#ifndef CORRECTEURPROPORTIONNEL_H
#define CORRECTEURPROPORTIONNEL_H
#include "correcteur.h"
#include <QObject>

class CorrecteurProportionnel : public Correcteur
{
public:
    CorrecteurProportionnel(QObject *parent = nullptr);

public slots:

       // void setConsigne(double nouvelleConsigne) { consigne = -nouvelleConsigne; }
      double process(double entree, double nouvelleConsigne);
private:
    double kp =1.53; // 0.00000007 1.53 0.033 : passe bien les virage serrer a droite
  // double consigne = 10000;

};

#endif // CORRECTEURPROPORTIONNEL_H
