#ifndef VEHICULE_H
#define VEHICULE_H

#include <QPointF>
#include "circuit.h"
#include "communicationtcp.h"
#include <QTimer>
using namespace  std;

class Vehicule : public QObject
{
    Q_OBJECT
public:
    Vehicule(int posX, int posY,int port,Circuit &_circuit);
    ~Vehicule();
    QPointF getPosition() const;

    void updateLidar();
    void initPos();

    QVector<QLineF> getLinesLidar() const;

    const array<int, 360> & getDistance() const;

    bool getIsConnected() const;

    std::chrono::time_point<std::chrono::high_resolution_clock> getTimeStartTour() const;

    int getBestTime() const;

    std::chrono::time_point<std::chrono::high_resolution_clock> getTimeStart() const;

    int getNbTour() const;

    bool getPenalite() const;

    void setIsEnable(bool newIsEnable);
    CommunicationTCP tcp;

public slots:
    void setIsCollisions(bool newIsCollisions);
    void start();
    void stop();

private:
    int maxDistanceLidar=12000;
    QPointF position;
    QPointF positionInit;
    double orientation;
    double orientationRadian();
    bool isConnected=false;
    bool isCollisions=true;
    bool isOnStartLine=false;
    bool waitFirstTour=true;
    bool isEnable=true;
    int nbTour=0;

    bool isRunning=false;
    bool penalite=false;

    Circuit &circuit;

    std::chrono::time_point<std::chrono::high_resolution_clock> timeStartTour,timeStart;
    int bestTime=9999999;

    const double largeurRobot;
    const double longueurRobot;

    double vitesse_mm_s;
    const double vMax_mm_s;


    double rayonCourbure=0;
    double angleRoues;
    const double angleRouesMax;

    double periode_ms;


    QVector<QLineF> linesLidar;
    int indiceMyLines=-1;

    QTimer tictoc;
    QTimer ticCapteurs;

    array<int,360> distance;

private slots:
    void move();
    void sendTcp();
    void getTcp(QStringList message);
    void connected();
    void disConnected();

private:
    void setVitesse(double v);
    void setDirection(double r);


};

#endif // VEHICULE_H
