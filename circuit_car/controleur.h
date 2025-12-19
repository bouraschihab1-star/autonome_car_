#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include "vehicule.h"
#include <QTimer>

class Controleur : public QObject
{
    Q_OBJECT
public:
    explicit Controleur(Vehicule *_voiture);

    Vehicule * voiture;
    QTimer tictoc;

private slots:
    void process();
signals:
};

#endif // CONTROLEUR_H
