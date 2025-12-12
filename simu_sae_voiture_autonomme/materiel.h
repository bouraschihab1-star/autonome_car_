#ifndef MATERIEL_H
#define MATERIEL_H
#include <QObject>

class Materiel : public QObject
{
    Q_OBJECT
public:

    explicit Materiel(QObject *parent = nullptr);
    std::array<int,360> distancesLidar;

signals:
    void newDistance();
    void newState(double vitesse, double angle);

public slots:

    virtual void deplacer(double vitesse,double angle)=0;

};


#endif // MATERIEL_H
