#include "circuitwidget.h"

#include <QDebug>
#include <QtMath>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

CircuitWidget::CircuitWidget(int _nbVoitures, QWidget *parent)
    : QWidget{parent}
    , nbVoitures(_nbVoitures)
    , voiture1(0,-2800,8880,circuit)
    , voiture2(-250,-2200,8881, circuit)
    , voiture3(-500,-2800,8882, circuit)
    , voiture4(-750,-2200,8883, circuit)
    , voiture5(-1000,-2800,8884, circuit)
    , voiture6(-1250,-2200,8885, circuit)
{

    voiture1.mutex.lock();
    voiture1.start();
    voiture1.mutex.lock();

    voiture2.mutex.lock();
    voiture2.start();
    voiture2.mutex.lock();

    voiture3.mutex.lock();
    voiture3.start();
    voiture3.mutex.lock();

    voiture4.mutex.lock();
    voiture4.start();
    voiture4.mutex.lock();

    voiture5.mutex.lock();
    voiture5.start();
    voiture5.mutex.lock();

    voiture6.mutex.lock();
    voiture6.start();
    voiture6.mutex.lock();

    tictoc.setInterval(30);
    connect(&tictoc,&QTimer::timeout,
            this,&CircuitWidget::maj);



    loadCircuit1();
    tictoc.start();


}

void CircuitWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    const int xCenter=width()/2;
    const int yCenter=height()/2;

    painter.translate(QPoint(xCenter,yCenter)+centre);
    painter.scale(zoom,zoom);

    pen.setWidth(5/zoom);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLines(circuit.linesDroit);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLines(circuit.linesGauche);
    pen.setWidth(10/zoom);
    pen.setColor(Qt::magenta);
    painter.setPen(pen);
    painter.drawLine(circuit.startLine);


    drawVehicule(voiture1.voiture,Qt::cyan,painter);
    drawVehicule(voiture2.voiture,Qt::darkRed,painter);
    drawVehicule(voiture3.voiture,Qt::blue,painter);
    drawVehicule(voiture4.voiture,Qt::magenta,painter);
    drawVehicule(voiture5.voiture,Qt::green,painter);
    drawVehicule(voiture6.voiture,Qt::gray,painter);


    pen.setColor(Qt::blue);
    pen.setWidth(50);
    painter.setPen(pen);
    painter.drawLines(circuit.linesVehicules);


    auto currentTime = high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    startTime=voiture1.voiture->getTimeStart();
    chrono::duration diff = duration_cast<std::chrono::milliseconds>(currentTime-startTime);
    emit newTimeVoiture(1,diff.count());
    emit newBestTimeVoiture(1,voiture1.voiture->getBestTime());
    emit newNbTour(1,voiture1.voiture->getNbTour());

    startTime=voiture2.voiture->getTimeStart();
    diff = duration_cast<std::chrono::milliseconds>(currentTime-startTime);
    emit newTimeVoiture(2,diff.count());
    emit newBestTimeVoiture(2,voiture2.voiture->getBestTime());
    emit newNbTour(2,voiture2.voiture->getNbTour());

    startTime=voiture3.voiture->getTimeStart();
    diff = duration_cast<std::chrono::milliseconds>(currentTime-startTime);
    emit newTimeVoiture(3,diff.count());
    emit newBestTimeVoiture(3,voiture3.voiture->getBestTime());
    emit newNbTour(3,voiture3.voiture->getNbTour());

    startTime=voiture4.voiture->getTimeStart();
    diff = duration_cast<std::chrono::milliseconds>(currentTime-startTime);
    emit newTimeVoiture(4,diff.count());
    emit newBestTimeVoiture(4,voiture4.voiture->getBestTime());
    emit newNbTour(4,voiture4.voiture->getNbTour());

    startTime=voiture5.voiture->getTimeStart();
    diff = duration_cast<std::chrono::milliseconds>(currentTime-startTime);
    emit newTimeVoiture(5,diff.count());
    emit newBestTimeVoiture(5,voiture5.voiture->getBestTime());
    emit newNbTour(5,voiture5.voiture->getNbTour());

    startTime=voiture6.voiture->getTimeStart();
    diff = duration_cast<std::chrono::milliseconds>(currentTime-startTime);
    emit newTimeVoiture(6,diff.count());
    emit newBestTimeVoiture(6,voiture6.voiture->getBestTime());
    emit newNbTour(6,voiture6.voiture->getNbTour());

}

void CircuitWidget::loadCircuit1()
{
    coteDroit.clear();
    coteGauche.clear();
    coteDroit.append(SegmentPiste(droit,2500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,1500));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,2000));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,1000));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,1000));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,1000));


    coteGauche.append(SegmentPiste(droit,4000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,2500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,2500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,2600));

    yposCoteDroit=-2000;
    yposCoteGauche=-3000;
    startLine=QLine(500,yposCoteDroit,500,yposCoteGauche);

    createCircuit();
}

void CircuitWidget::loadCircuit2()
{
    coteDroit.clear();
    coteGauche.clear();
    coteDroit.append(SegmentPiste(droit,2500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,1500));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,2000));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,1000));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,1000));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,1000));


    coteGauche.append(SegmentPiste(droit,4000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,2500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,2500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1500));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,2600));

    yposCoteDroit=-2000;
    yposCoteGauche=-3000;
    startLine=QLine(500,yposCoteDroit,500,yposCoteGauche);

    createCircuit();
}

void CircuitWidget::loadCircuit3()
{
    coteDroit.clear();
    coteDroit.append(SegmentPiste(droit,2500));
    coteDroit.append(SegmentPiste(virageM45,500));
    coteDroit.append(SegmentPiste(droit,500));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,2500));
    coteDroit.append(SegmentPiste(virageM45,500));
    coteDroit.append(SegmentPiste(droit,500));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,1000));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,500));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,500));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,500));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,5000));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,4000));
    coteDroit.append(SegmentPiste(virageM45,500));
    coteDroit.append(SegmentPiste(droit,500));
    coteDroit.append(SegmentPiste(virageM45,500));
    coteDroit.append(SegmentPiste(droit,2000));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,100));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,100));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,100));
    coteDroit.append(SegmentPiste(virageP45,500));
    coteDroit.append(SegmentPiste(droit,6000));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(virageP90,500));
    coteDroit.append(SegmentPiste(droit,2500));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,5000));
    coteDroit.append(SegmentPiste(virageM90,500));
    coteDroit.append(SegmentPiste(droit,10000));
    coteDroit.append(SegmentPiste(virageP90,200));
    coteDroit.append(SegmentPiste(droit,80));
    coteDroit.append(SegmentPiste(virageP90,200));
    coteDroit.append(SegmentPiste(droit,9000));

    coteGauche.clear();
    coteGauche.append(SegmentPiste(droit,2500));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,500));
    coteGauche.append(SegmentPiste(virageM45,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageM45,500));
    coteGauche.append(SegmentPiste(droit,500));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,1000));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,1000));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,3000));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,1000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,10000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,3000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,1000));
    coteGauche.append(SegmentPiste(virageP45,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageM45,500));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,2000));
    coteGauche.append(SegmentPiste(virageM90,500));
    coteGauche.append(SegmentPiste(droit,10000));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,4100));
    coteGauche.append(SegmentPiste(virageP90,500));
    coteGauche.append(SegmentPiste(droit,11000));

    yposCoteDroit=-1250;
    yposCoteGauche=-3750;
    startLine=QLine(500,yposCoteDroit,500,yposCoteGauche);
    createCircuit();
}

void CircuitWidget::loadCircuit4()
{
    coteDroit.clear();
    coteGauche.clear();

    createCircuit();
}

void CircuitWidget::zoomPlus()
{
    zoom+=0.005;
}

void CircuitWidget::zoomMoins()
{
    if (zoom>0) zoom-=0.005;
}

void CircuitWidget::moveHaut()
{
    centre+=QPoint(0,-10);
}

void CircuitWidget::moveBas()
{
    centre+=QPoint(0,10);
}

void CircuitWidget::moveDroit()
{
    centre+=QPoint(10,0);
}

void CircuitWidget::moveGauche()
{
    centre+=QPoint(-10,0);
}

void CircuitWidget::createCircuit()
{
    updateLines(coteDroit,circuit.linesDroit,yposCoteDroit);
    updateLines(coteGauche,circuit.linesGauche,yposCoteGauche);
    circuit.startLine=startLine;

    voiture1.voiture->initPos();
    voiture2.voiture->initPos();
    voiture3.voiture->initPos();
    voiture4.voiture->initPos();
    voiture5.voiture->initPos();
    voiture6.voiture->initPos();

}

void CircuitWidget::updateLines(const QList<SegmentPiste> &cote, QVector<QLineF> &lines, int decalageY)
{
    lines.clear();

    QPointF startPoint;
    QPointF endPoint;
    int angle;


    startPoint=QPointF(0,decalageY);
    angle=0;


    for (const auto& sgt: cote)
    {
        double angleRad=qDegreesToRadians((double)angle);
        if (sgt.type==droit)
        {
            endPoint=startPoint+QPointF(sgt.longueur*qCos(angleRad),sgt.longueur*qSin(angleRad));
            lines.append(QLineF(startPoint,endPoint));
            startPoint=endPoint;
        }
        else if (sgt.type==virageP90)
        {
            double deltaAngle=10;
            double deltaAngleRad=qDegreesToRadians((double)deltaAngle);
            for(int i=1;i<=90;i+=deltaAngle)
            {
                angle+=deltaAngle;
                double angleRad=qDegreesToRadians((double)angle);
                endPoint=startPoint+QPointF(sgt.longueur*deltaAngleRad*qCos(angleRad),
                                            sgt.longueur*deltaAngleRad*qSin(angleRad));
                lines.append(QLineF(startPoint,endPoint));
                startPoint=endPoint;
            }
        }
        else if (sgt.type==virageM90)
        {
            double deltaAngle=10;
            double deltaAngleRad=qDegreesToRadians((double)deltaAngle);
            for(int i=-1;i>=-90;i-=deltaAngle)
            {
                angle-=deltaAngle;
                double angleRad=qDegreesToRadians((double)angle);
                endPoint=startPoint+QPointF(sgt.longueur*deltaAngleRad*qCos(angleRad),
                                                sgt.longueur*deltaAngleRad*qSin(angleRad));
                lines.append(QLineF(startPoint,endPoint));
                startPoint=endPoint;
            }
        }
        else if (sgt.type==virageP45)
        {
            double deltaAngle=15;
            double deltaAngleRad=qDegreesToRadians((double)deltaAngle);
            for(int i=1;i<=45;i+=deltaAngle)
            {
                angle+=deltaAngle;
                double angleRad=qDegreesToRadians((double)angle);
                endPoint=startPoint+QPointF(sgt.longueur*deltaAngleRad*qCos(angleRad),
                                                sgt.longueur*deltaAngleRad*qSin(angleRad));
                lines.append(QLineF(startPoint,endPoint));
                startPoint=endPoint;
            }
        }
        else if (sgt.type==virageM45)
        {
            double deltaAngle=15;
            double deltaAngleRad=qDegreesToRadians((double)deltaAngle);
            for(int i=-1;i>=-45;i-=deltaAngle)
            {
                angle-=deltaAngle;
                double angleRad=qDegreesToRadians((double)angle);
                endPoint=startPoint+QPointF(sgt.longueur*deltaAngleRad*qCos(angleRad),
                                                sgt.longueur*deltaAngleRad*qSin(angleRad));
                lines.append(QLineF(startPoint,endPoint));
                startPoint=endPoint;
            }
        }
        else
        {
            qDebug()<<"type de segment à ajouter !!!";
        }
    }



}

void CircuitWidget::drawVehicule(Vehicule *vehicule, const QColor &color, QPainter &painter)
{
    QPen pen;
    pen.setWidth(4);
    pen.setColor(color);
    painter.setBrush(color);
    painter.setPen(pen);
    if ((showLidar==true)and(vehicule->getIsConnected()))   painter.drawLines(vehicule->getLinesLidar());
    else                                                    painter.drawEllipse(vehicule->getPosition(),70,70);
    if (vehicule->getPenalite()==true)
    {
        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.setBrush(Qt::red);
        painter.drawEllipse(vehicule->getPosition(),30,30);
    }
}

void CircuitWidget::maj()
{
    update();
}

void CircuitWidget::enableLidar(bool state)
{
    showLidar=state;
}

