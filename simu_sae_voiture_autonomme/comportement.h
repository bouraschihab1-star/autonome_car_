#ifndef COMPORTEMENT_H
#define COMPORTEMENT_H
#include <array>

#include <QObject>
using namespace std;
class Comportement : public QObject
{
    Q_OBJECT
public:
    explicit Comportement(array<int, 360> & _distancesLidar);

    array<int, 360> &distancesLidar;

signals:
    void deplacer(double vitesse, double angle);
public slots:
    virtual void process()=0;


};

#endif // COMPORTEMENT_H
