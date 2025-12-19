#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int nbVoitures, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , circuit(nbVoitures,this)
{
    ui->setupUi(this);
    ui->circuitPosition->layout()->addWidget(&circuit);

    ui->bpResetVoiture1->setStyleSheet("background-color:cyan;");
    ui->bpResetVoiture2->setStyleSheet("background-color:darkRed;");
    ui->bpResetVoiture3->setStyleSheet("background-color:blue;");
    ui->bpResetVoiture4->setStyleSheet("background-color:magenta;");
    ui->bpResetVoiture5->setStyleSheet("background-color:green;");
    ui->bpResetVoiture6->setStyleSheet("background-color:gray;");


    ui->checkBox_1->setStyleSheet("background-color:cyan;");
    ui->checkBox_2->setStyleSheet("background-color:darkRed;");
    ui->checkBox_3->setStyleSheet("background-color:blue;");
    ui->checkBox_4->setStyleSheet("background-color:magenta;");
    ui->checkBox_5->setStyleSheet("background-color:green;");
    ui->checkBox_6->setStyleSheet("background-color:gray;");

    ui->enableVoiture_1->setStyleSheet("background-color:cyan;");
    ui->enableVoiture_2->setStyleSheet("background-color:darkRed;");
    ui->enableVoiture_3->setStyleSheet("background-color:blue;");
    ui->enableVoiture_4->setStyleSheet("background-color:magenta;");
    ui->enableVoiture_5->setStyleSheet("background-color:green;");
    ui->enableVoiture_6->setStyleSheet("background-color:gray;");


    ui->voitureTime1->setStyleSheet("background-color:cyan;");
    ui->voitureBestTime1->setStyleSheet("background-color:cyan;");
    ui->voitureTime2->setStyleSheet("background-color:darkRed;");
    ui->voitureBestTime2->setStyleSheet("background-color:darkRed;");
    ui->voitureTime3->setStyleSheet("background-color:blue;");
    ui->voitureBestTime3->setStyleSheet("background-color:blue;");
    ui->voitureTime4->setStyleSheet("background-color:magenta;");
    ui->voitureBestTime4->setStyleSheet("background-color:magenta;");
    ui->voitureTime5->setStyleSheet("background-color:green;");
    ui->voitureBestTime5->setStyleSheet("background-color:green;");
    ui->voitureTime6->setStyleSheet("background-color:gray;");
    ui->voitureBestTime6->setStyleSheet("background-color:gray;");

    ui->checkBox_1->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->checkBox_5->setChecked(true);
    ui->checkBox_6->setChecked(true);

    ui->checkBox_all->setChecked(true);

    connect(ui->initTcp,&QPushButton::clicked,
            &circuit.voiture1.voiture->tcp,&CommunicationTCP::reStartConnexion);
    connect(ui->initTcp,&QPushButton::clicked,
            &circuit.voiture2.voiture->tcp,&CommunicationTCP::reStartConnexion);
    connect(ui->initTcp,&QPushButton::clicked,
            &circuit.voiture3.voiture->tcp,&CommunicationTCP::reStartConnexion);
    connect(ui->initTcp,&QPushButton::clicked,
            &circuit.voiture4.voiture->tcp,&CommunicationTCP::reStartConnexion);
    connect(ui->initTcp,&QPushButton::clicked,
            &circuit.voiture5.voiture->tcp,&CommunicationTCP::reStartConnexion);
    connect(ui->initTcp,&QPushButton::clicked,
            &circuit.voiture6.voiture->tcp,&CommunicationTCP::reStartConnexion);

    connect(ui->enableVoiture_1,&QCheckBox::clicked,
            circuit.voiture1.voiture,&Vehicule::setIsEnable);
    connect(ui->enableVoiture_2,&QCheckBox::clicked,
            circuit.voiture2.voiture,&Vehicule::setIsEnable);
    connect(ui->enableVoiture_3,&QCheckBox::clicked,
            circuit.voiture3.voiture,&Vehicule::setIsEnable);
    connect(ui->enableVoiture_4,&QCheckBox::clicked,
            circuit.voiture4.voiture,&Vehicule::setIsEnable);
    connect(ui->enableVoiture_5,&QCheckBox::clicked,
            circuit.voiture5.voiture,&Vehicule::setIsEnable);
    connect(ui->enableVoiture_6,&QCheckBox::clicked,
            circuit.voiture6.voiture,&Vehicule::setIsEnable);


    connect(ui->checkBox_1,&QCheckBox::clicked,
            circuit.voiture1.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_2,&QCheckBox::clicked,
            circuit.voiture2.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_3,&QCheckBox::clicked,
            circuit.voiture3.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_4,&QCheckBox::clicked,
            circuit.voiture4.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_5,&QCheckBox::clicked,
            circuit.voiture5.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_6,&QCheckBox::clicked,
            circuit.voiture6.voiture,&Vehicule::setIsCollisions);

    connect(ui->checkBox_all,&QCheckBox::clicked,
            circuit.voiture1.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            circuit.voiture2.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            circuit.voiture3.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            circuit.voiture4.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            circuit.voiture5.voiture,&Vehicule::setIsCollisions);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            circuit.voiture6.voiture,&Vehicule::setIsCollisions);


    connect(ui->checkBox_all,&QCheckBox::clicked,
            ui->checkBox_1,&QCheckBox::setChecked);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            ui->checkBox_2,&QCheckBox::setChecked);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            ui->checkBox_3,&QCheckBox::setChecked);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            ui->checkBox_4,&QCheckBox::setChecked);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            ui->checkBox_5,&QCheckBox::setChecked);
    connect(ui->checkBox_all,&QCheckBox::clicked,
            ui->checkBox_6,&QCheckBox::setChecked);


    /*QPushButton * bp;
    for (int i=0;i<nbVoitures;i++)
    {
        bp = new QPushButton();
        ui->barreHaut->layout()->addWidget(bp);
        bp->setText("init V"+QString::number(i));
    }*/


    connect(ui->bpResetVoiture1,&QPushButton::clicked,
            circuit.voiture1.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoiture2,&QPushButton::clicked,
            circuit.voiture2.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoiture3,&QPushButton::clicked,
            circuit.voiture3.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoiture4,&QPushButton::clicked,
            circuit.voiture4.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoiture5,&QPushButton::clicked,
            circuit.voiture5.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoiture6,&QPushButton::clicked,
            circuit.voiture6.voiture,&Vehicule::initPos);

    connect(ui->bpResetVoitureAll,&QPushButton::clicked,
            circuit.voiture1.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoitureAll,&QPushButton::clicked,
            circuit.voiture2.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoitureAll,&QPushButton::clicked,
            circuit.voiture3.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoitureAll,&QPushButton::clicked,
            circuit.voiture4.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoitureAll,&QPushButton::clicked,
            circuit.voiture5.voiture,&Vehicule::initPos);
    connect(ui->bpResetVoitureAll,&QPushButton::clicked,
            circuit.voiture6.voiture,&Vehicule::initPos);

    // bps choix circuit

    connect(ui->bpCircuit_1,&QPushButton::clicked,
            &circuit,&CircuitWidget::loadCircuit1);
    connect(ui->bpCircuit_2,&QPushButton::clicked,
            &circuit,&CircuitWidget::loadCircuit2);
    connect(ui->bpCircuit_3,&QPushButton::clicked,
            &circuit,&CircuitWidget::loadCircuit3);
    connect(ui->bpCircuit_4,&QPushButton::clicked,
            &circuit,&CircuitWidget::loadCircuit4);

    connect(ui->bpZoomPlus,&QPushButton::clicked,
            &circuit,&CircuitWidget::zoomPlus);
    connect(ui->bpZoomMoins,&QPushButton::clicked,
            &circuit,&CircuitWidget::zoomMoins);

    connect(ui->bpMoveUp,&QPushButton::clicked,
            &circuit,&CircuitWidget::moveHaut);
    connect(ui->bpMoveDown,&QPushButton::clicked,
            &circuit,&CircuitWidget::moveBas);
    connect(ui->bpMoveDroit,&QPushButton::clicked,
            &circuit,&CircuitWidget::moveDroit);
    connect(ui->bpMoveGauche,&QPushButton::clicked,
            &circuit,&CircuitWidget::moveGauche);

    connect(&circuit,&CircuitWidget::newTimeVoiture,
            this,&MainWindow::newTimeVoiture);
    connect(&circuit,&CircuitWidget::newBestTimeVoiture,
            this,&MainWindow::newBestTimeVoiture);
    connect(&circuit,&CircuitWidget::newNbTour,
            this,&MainWindow::newNbTours);

    connect(ui->checkLidar,&QCheckBox::clicked,
            &circuit,&CircuitWidget::enableLidar);

    connect(ui->bpStart,&QPushButton::clicked,
            this,&MainWindow::start);
    connect(ui->bpStop,&QPushButton::clicked,
            this,&MainWindow::stop);

    resize(1000,900);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newTimeVoiture(int voiture, int time)
{
    QLCDNumber * lcd=nullptr;
    switch (voiture) {
    case 1:lcd=ui->voitureTime1;break;
    case 2:lcd=ui->voitureTime2;break;
    case 3:lcd=ui->voitureTime3;break;
    case 4:lcd=ui->voitureTime4;break;
    case 5:lcd=ui->voitureTime5;break;
    case 6:lcd=ui->voitureTime6;break;
    default:
        break;
    }
    if (time>99999) time=0;
    if (time<0) time=0;
    if (lcd!=nullptr) lcd->display(time);
}

void MainWindow::newBestTimeVoiture(int voiture, int time)
{
    QLCDNumber * lcd=nullptr;
    switch (voiture) {
    case 1:lcd=ui->voitureBestTime1;break;
    case 2:lcd=ui->voitureBestTime2;break;
    case 3:lcd=ui->voitureBestTime3;break;
    case 4:lcd=ui->voitureBestTime4;break;
    case 5:lcd=ui->voitureBestTime5;break;
    case 6:lcd=ui->voitureBestTime6;break;
    default:
        break;
    }
    if (time>99999) time=0;
    if (lcd!=nullptr) lcd->display(time);
}

void MainWindow::newNbTours(int voiture, int nb)
{
    QLCDNumber * lcd=nullptr;
    switch (voiture) {
    case 1:lcd=ui->nbTour1;break;
    case 2:lcd=ui->nbTour2;break;
    case 3:lcd=ui->nbTour3;break;
    case 4:lcd=ui->nbTour4;break;
    case 5:lcd=ui->nbTour5;break;
    case 6:lcd=ui->nbTour6;break;
    default:
        break;
    }
    if (lcd!=nullptr) lcd->display(nb);
}

void MainWindow::start()
{
    ui->bpStart->setDisabled(true);
    ui->bpStop->setEnabled(true);

    circuit.voiture1.voiture->start();
    circuit.voiture2.voiture->start();
    circuit.voiture3.voiture->start();
    circuit.voiture4.voiture->start();
    circuit.voiture5.voiture->start();
    circuit.voiture6.voiture->start();
}

void MainWindow::stop()
{
    ui->bpStart->setEnabled(true);
    ui->bpStop->setDisabled(true);

    circuit.voiture1.voiture->stop();
    circuit.voiture2.voiture->stop();
    circuit.voiture3.voiture->stop();
    circuit.voiture4.voiture->stop();
    circuit.voiture5.voiture->stop();
    circuit.voiture6.voiture->stop();
}
