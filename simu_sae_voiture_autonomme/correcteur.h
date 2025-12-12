#ifndef CORRECTEUR_H
#define CORRECTEUR_H
#include <QObject>
#include <QDebug>


class Correcteur : public QObject
{
    Q_OBJECT
public:
    explicit Correcteur(QObject *parent = nullptr);
public slots:
    virtual double process(double entree, double nouvelleConsigne) = 0;
    //  virtual void setConsigne(double) {}
protected:


};


#endif // CORRECTEUR_H
