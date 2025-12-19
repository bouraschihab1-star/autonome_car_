#include "vehicule.h"
#include <QtMath>
#include <QDebug>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

Vehicule::Vehicule(int posX, int posY, int port, Circuit &_circuit)
    : tcp(port)
    , circuit(_circuit)
    , largeurRobot(180)
    , longueurRobot(360)
    , vMax_mm_s(4000)
    , angleRouesMax(20)
    , periode_ms(1)
{
    for (int i=0;i<360;i++) linesLidar.append(QLineF());
    indiceMyLines=circuit.linesVehicules.size();
    for (int i=0;i<4;i++) circuit.linesVehicules.append(QLineF());

    positionInit=QPoint(posX,posY);
    orientation=0;
    tictoc.setInterval(periode_ms);
    connect(&tictoc,&QTimer::timeout,
            this,&Vehicule::move);
    ticCapteurs.setInterval(50);
    connect(&ticCapteurs,&QTimer::timeout,
            this,&Vehicule::sendTcp);

    connect(&tcp,&CommunicationTCP::newValue,this,&Vehicule::getTcp);
    connect(&tcp,&CommunicationTCP::disConnected,this,&Vehicule::disConnected);
    connect(&tcp,&CommunicationTCP::connected,this,&Vehicule::connected);

    tictoc.start();

    initPos();
}

Vehicule::~Vehicule()
{

}

QPointF Vehicule::getPosition() const
{
    return position;
}

void Vehicule::updateLidar()
{
    for (auto& line: linesLidar)
    {
        line.setP1(position);
    }
    int angle=-180;
    for (auto& line: linesLidar)
    {
        double angleRad=qDegreesToRadians((double)angle);
        line.setP2(position+QPointF(maxDistanceLidar*cos(orientationRadian()-angleRad),
                                      maxDistanceLidar*sin(orientationRadian()-angleRad)));

        QPointF p;
        for (auto& intersectionLine: circuit.linesDroit)
        {
            if (line.intersects(intersectionLine,&p)==QLineF::BoundedIntersection)
            {
                line.setP2(p);
            }
        }
        for (auto& intersectionLine: circuit.linesGauche)
        {
            if (line.intersects(intersectionLine,&p)==QLineF::BoundedIntersection)
            {
                line.setP2(p);
            }
        }
        int i=0;
        for (auto& intersectionLine: circuit.linesVehicules)
        {
            if (    (i!=indiceMyLines+0)
                and (i!=indiceMyLines+1)
                and (i!=indiceMyLines+3))
            {
                if (((i!=indiceMyLines+2)and(isCollisions==true)) or
                    ((i==indiceMyLines+2)and(angle!=-180)))
                    if (line.intersects(intersectionLine,&p)==QLineF::BoundedIntersection)
                    {
                        line.setP2(p);
                    }
            }
            i++;
        }
        angle++;
    }
    for (int i=0;i<360;i++)
    {
        distance.at(i)=linesLidar.at(i).length();
    }
}

void Vehicule::initPos()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
    position=positionInit;
    orientation=0;
    waitFirstTour=true;
    bestTime=9999999;
    timeStartTour=time;
    timeStart=time;
    nbTour=0;
    penalite=false;
}


QVector<QLineF> Vehicule::getLinesLidar() const
{
    return linesLidar;
}

double Vehicule::orientationRadian()
{
    return qDegreesToRadians(orientation);
}

void Vehicule::setIsEnable(bool newIsEnable)
{
    isEnable = newIsEnable;
    if (isEnable) initPos();
    else
    {
        stop();
        position=QPointF(-999999,-999999);
    }
}

bool Vehicule::getPenalite() const
{
    return penalite;
}

int Vehicule::getNbTour() const
{
    return nbTour;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Vehicule::getTimeStart() const
{
    return timeStart;
}

int Vehicule::getBestTime() const
{
    return bestTime;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Vehicule::getTimeStartTour() const
{
    return timeStartTour;
}

void Vehicule::setIsCollisions(bool newIsCollisions)
{
    isCollisions = newIsCollisions;
}

void Vehicule::start()
{
    isRunning=true;
    if (vitesse_mm_s!=0) penalite=true;
}

void Vehicule::stop()
{
    isRunning=false;
}

bool Vehicule::getIsConnected() const
{
    return isConnected;
}

const array<int, 360> & Vehicule::getDistance() const
{
    return distance;
}

void Vehicule::move()
{
    if (isRunning and isEnable)
    //if (orientation<180) orientation++; else orientation=-180;
    {
        double distance=(vitesse_mm_s*periode_ms)/1000.0;
        double dTeta=0;
        if (rayonCourbure!=0)
        {
            dTeta=distance/rayonCourbure;
        }
        orientation-=qRadiansToDegrees(dTeta);
        //orientation+=0.05;
        position+=QPointF(distance*cos(qDegreesToRadians(-orientation)),distance*sin(qDegreesToRadians(+orientation)));
    }

    QPointF avDroit=position+QPointF(-largeurRobot/2*sin(qDegreesToRadians(orientation))+longueurRobot/2*cos(qDegreesToRadians(orientation))
                                          ,largeurRobot/2*cos(qDegreesToRadians(-orientation))+longueurRobot/2*sin(qDegreesToRadians(orientation)));
    QPointF avGauche=position+QPointF(largeurRobot/2*sin(qDegreesToRadians(orientation))+longueurRobot/2*cos(qDegreesToRadians(orientation))
                                          ,-largeurRobot/2*cos(qDegreesToRadians(-orientation))+longueurRobot/2*sin(qDegreesToRadians(orientation)));

    QPointF arDroit=position+QPointF(-largeurRobot/2*sin(qDegreesToRadians(orientation))-longueurRobot/2*cos(qDegreesToRadians(orientation))
                                         ,largeurRobot/2*cos(qDegreesToRadians(-orientation))-longueurRobot/2*sin(qDegreesToRadians(orientation)));
    QPointF arGauche=position+QPointF(largeurRobot/2*sin(qDegreesToRadians(orientation))-longueurRobot/2*cos(qDegreesToRadians(orientation))
                                          ,-largeurRobot/2*cos(qDegreesToRadians(-orientation))-longueurRobot/2*sin(qDegreesToRadians(orientation)));

    circuit.linesVehicules[indiceMyLines+0].setP1(avDroit);
    circuit.linesVehicules[indiceMyLines+0].setP2(avGauche);

    circuit.linesVehicules[indiceMyLines+1].setP1(avDroit);
    circuit.linesVehicules[indiceMyLines+1].setP2(arDroit);

    circuit.linesVehicules[indiceMyLines+2].setP1(arDroit);
    circuit.linesVehicules[indiceMyLines+2].setP2(arGauche);

    circuit.linesVehicules[indiceMyLines+3].setP1(arGauche);
    circuit.linesVehicules[indiceMyLines+3].setP2(avGauche);
    // passage de la ligne d'arrivée
    QPointF p;
    if (circuit.startLine.intersects(circuit.linesVehicules[indiceMyLines+1],&p)==QLineF::BoundedIntersection)
    {
        if (isOnStartLine==false)
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> currentTime=high_resolution_clock::now();
            chrono::duration diff = duration_cast<std::chrono::milliseconds>(currentTime-timeStartTour);
            int duree=diff.count();
            if (waitFirstTour==false)
            {
                if (duree<bestTime) bestTime=duree;
                nbTour++;
            }
            else
            {
                    timeStart=currentTime;
            }
            timeStartTour=currentTime;
            waitFirstTour=false;
        }
        isOnStartLine=true;
    }
    else
    {
        isOnStartLine=false;
    }

}

void Vehicule::sendTcp()
{
    updateLidar();
    QString message;
    for (int i=0;i<360;i++)
    {
        message.append(QString::number(distance.at(i)));
        if (i!=359)message.append(";");
    }
    tcp.sendDatas(message);
}

void Vehicule::getTcp(QStringList message)
{
    setVitesse(message.at(0).toDouble());
    setDirection(message.at(1).toDouble());
}

void Vehicule::connected()
{
    isConnected=true;
    ticCapteurs.start();
}

void Vehicule::disConnected()
{
    isConnected=false;
    ticCapteurs.stop();
    setVitesse(0);
    setDirection(0);

}

void Vehicule::setVitesse(double r)
{
    if (r<-1) r=-1;
    if (r>1) r=1;
    vitesse_mm_s=vMax_mm_s*r;
}

void Vehicule::setDirection(double r)
{
    if (r>1) r=1;
    if (r<-1) r=-1;
    angleRoues=angleRouesMax*r;

    if (angleRoues==0) rayonCourbure=0;
    else rayonCourbure=longueurRobot/qSin(qDegreesToRadians(angleRoues));
}
