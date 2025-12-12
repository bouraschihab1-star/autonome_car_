#include "suivrebord.h"
#include <array>
#include "comportement.h"



#include <QDebug>

SuivreBord::SuivreBord(array<int, 360> & _distancesLidar ,Correcteur& _c )
    :Comportement(_distancesLidar),
    c (_c)
{

}

void SuivreBord::process()
{



        double vitesse = 0.3;



        /// --- Consigne dynamique ---

        double AvantDroite = 0;
        for (int i = 150; i <= 190; i++) {
            AvantDroite += distancesLidar[i];
        }
        double moyAvantDroite = AvantDroite / (190 - 150 + 1);



        double AvantGauche = 0;
        for (int i = 170; i <= 210; i++) {
            AvantGauche += distancesLidar[i];
        }
        double moyAvantGauche = AvantGauche / (210 - 170 + 1);





        double diff;// = distancesLidar[90] - distancesLidar[270];//avantDroite - avantGauche;

        double distTOTAL = distancesLidar[90] + distancesLidar[270]; //mesure de l'espace du circuit niveau largeur


        // --- distance de securité a ne pas depassé sur la consigne ---

        if(distancesLidar[90] >= distTOTAL){diff= distTOTAL +200;}
        else if(distancesLidar[270] >= distTOTAL){diff= distTOTAL - 200;}


        // --- Moyenne droite/gauche spécifique au placement consigne ---

        if(moyAvantDroite >= moyAvantGauche){diff= distTOTAL*0.10;}
        else if(moyAvantDroite <= moyAvantGauche){diff= distTOTAL*0.9;}



        static double consigneFiltree = 0.0;
        double consigneDynamique = -diff*0.01; // à ajuster selon ton échelle LIDAR

        double alpha = 0.03; // Ajustable : plus petit = plus stable
        consigneFiltree = consigneFiltree * (1 - alpha) + consigneDynamique * alpha;







        /// --- Moyenne droite/gauche ---
        double sommeDroite = 0;
        for (int i = 80; i <= 180; i++) {
            sommeDroite += distancesLidar[i];
        }
        double moyDroite = sommeDroite / (175 - 80 + 1);



        double sommeDroite2 = 0;
        for (int i = 120; i <= 160; i++) {
            sommeDroite2 += distancesLidar[i];
        }
        double moyDroite2 = sommeDroite2 / (160 - 120 + 1);





        double sommeGauche = 0;
        for (int i = 190; i <= 278; i++) {
            sommeGauche += distancesLidar[i];
        }
        double moyGauche = sommeGauche / (278 - 190 + 1);



        double sommeGauche2 = 0;
        for (int i = 190; i <= 210; i++) {
            sommeGauche2 += distancesLidar[i];
        }
        double moyGauche2 = sommeGauche2 / (210 - 190 + 1);



        /// --- calcul de l'angle avec correction ---


        double angle = c.process( moyDroite2 - moyGauche, consigneFiltree);


        /// --- HYSTERESIS DANS LES VIRAGES SERRÉS ---

        static double angleOld = 0.0;   // mémorise le dernier angle efficace
        static double seuilDiff = 100.0; // seuil minimal pour considérer une vraie différence de mur

        double diffMur = moyDroite - moyGauche2;

        //Si la différence est trop petite → virage ambigu → on garde l’ancien angle
        if (diffMur < seuilDiff)
        {
            angle = -1;
        }
        else if(diffMur < -seuilDiff){ angle = 1;}
        // else
        // {
        //     angleOld = angle; // sinon on met à jour
        // }



        /// /--- Sécurité virage serré (optionnel) ---
        // if (moyDroite >= moyGauche) {
        //    // vitesse = 0.01;
        //     angle -= 1;
        // }
        // if (/*distancesLidar[82]*/moyDroite < -80){//&& moyDroite > moyGauche) {
        //     vitesse = 0.2;
        //     angle -= 100;

        // }

   emit deplacer(vitesse, angle);
    qDebug() << "SuivreBord::process -> deplacer emitted:" << vitesse << angle;
    qDebug() << "valeur tout droit" << distancesLidar[180] ;
     // qDebug() << "valeur droite" << distancesLidar[82] ;
     //  qDebug() << "valeur gauche" << distancesLidar[243] ;
     qDebug() << "moy droite" << moyDroite ;
     qDebug() << "moy gauche" << moyGauche2 ;
    qDebug() << "diff moy" << moyDroite - moyGauche2;
      qDebug() << "angle" << angle ;

}
