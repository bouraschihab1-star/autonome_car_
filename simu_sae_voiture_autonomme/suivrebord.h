#ifndef SUIVREBORD_H
#define SUIVREBORD_H

#include "comportement.h"
#include "correcteur.h"
#include <QObject>



class SuivreBord : public Comportement
{
        Q_OBJECT

public:
    explicit SuivreBord(array<int, 360> & _distancesLidar, Correcteur& _c );
    double _lastError = 0.0;
public slots:
    void process();
private:
    QString data;
    Correcteur& c;



};


#endif // SUIVREBORD_H

