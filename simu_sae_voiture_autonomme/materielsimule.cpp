#include "materielsimule.h"
#include "tcpclient.h"
#include <QDebug>

MaterielSimule::MaterielSimule(int _numPort)
    : tcp("192.168.1.79",_numPort),numPort(_numPort)  // 172.20.10.5 ou 192.168.1.79
{


}

void MaterielSimule::deplacer(double vitesse, double angle)
{
    QString newdata = QString::number(vitesse, 'f', 2) + ";" + QString::number(angle, 'f', 2);
   tcp.sendDatas(newdata);
    qDebug() <<"NEWDATA ENVOYER";

}

void MaterielSimule::processTcpDatas(QString data)
{
    QStringList valeurLidar = data.split(";");

    if (valeurLidar.size() == 360){
        for (int i = 0; i < distancesLidar.size(); ++i) {
            distancesLidar[i] = valeurLidar[i].toInt();

        }
    } else
    {
        qDebug() <<"la chaine de caractere n'est pas de la bonne taille";
    }

    emit newDistance();
    qDebug() <<"signal newDistance emis";
}
