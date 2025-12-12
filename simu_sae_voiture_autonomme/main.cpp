//#include "mainwindow.h"
#include "materielsimule.h"
#include "correcteurproportionnel.h"
#include "suivrebord.h"
#include "tcpserveur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  // MainWindow w;
  //  w.show();
    TcpServeur serveur1;
    qInfo()<<"serveur creer";
    MaterielSimule m1(8883);
    CorrecteurProportionnel correction1;
    SuivreBord suiv1(m1.distancesLidar, correction1);

    QObject::connect(&m1.tcp, &TcpClient::newDatas,
                    &m1, &MaterielSimule::processTcpDatas);

   // QObject::connect(&m1.tcp, &TcpClient::newDatas,
                //    &serveur1, &TcpServeur::sendDatas);

    QObject::connect(&m1, &MaterielSimule::newDistance, &suiv1, &SuivreBord::process);

    //  quand le comportement calcule une commande -> appeler deplacer() du materiel simulé
    QObject::connect(&suiv1, &SuivreBord::deplacer, &m1, &MaterielSimule::deplacer);

    QObject::connect(&serveur1, &TcpServeur::newDatas, &suiv1, &SuivreBord::process);


    //signal pour connecter emit data newdata dans suivrebord

    // -> maintenant : réception TCP -> emit newDistance -> suiv1.process() -> emit commande -> m1.deplacer()


    return a.exec();
}
