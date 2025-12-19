#ifndef CIRCUITWIDGET_H
#define CIRCUITWIDGET_H

#include <QWidget>
#include <QList>
#include <QLineF>
#include "segmentpiste.h"
#include "vehicule.h"
#include "circuit.h"
#include "vehiculethread.h"
#include <QTimer>
#include <QPainter>

class CircuitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CircuitWidget(int _nbVoitures,QWidget *parent = nullptr);
    Circuit circuit;

    const int nbVoitures;
    double zoom=0.1;
    QPoint centre;
    //QVector<VehiculeThread> voituresThreads;
    VehiculeThread voiture1;
    VehiculeThread voiture2;
    VehiculeThread voiture3;
    VehiculeThread voiture4;
    VehiculeThread voiture5;
    VehiculeThread voiture6;

protected:
    void paintEvent(QPaintEvent *event) override;

    QList <SegmentPiste>  coteDroit;
    QList <SegmentPiste>  coteGauche;
    int yposCoteDroit;
    int yposCoteGauche;
    QLine startLine;

    QTimer tictoc;

    bool showLidar=true;

    void createCircuit();



    void updateLines(const QList <SegmentPiste> &cote,QVector<QLineF> &lines,int decalageY);
    void drawVehicule(Vehicule *vehicule, const QColor &color,QPainter &painter);

private slots:
    void maj();

public slots:
    void enableLidar(bool state);

    void loadCircuit1();
    void loadCircuit2();
    void loadCircuit3();
    void loadCircuit4();
    void zoomPlus();
    void zoomMoins();

    void moveHaut();
    void moveBas();
    void moveDroit();
    void moveGauche();

signals:
    void newTimeVoiture(int voiture,int time);
    void newBestTimeVoiture(int voiture,int time);
    void newNbTour(int voiture,int time);
};

#endif // CIRCUITWIDGET_H
