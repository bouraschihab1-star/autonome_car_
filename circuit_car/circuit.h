#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <QVector>
#include <QLineF>

class Circuit
{
public:
    Circuit();

    QVector<QLineF> linesDroit;
    QVector<QLineF> linesGauche;
    QVector<QLineF> linesVehicules;

    QLineF startLine;

};

#endif // CIRCUIT_H
