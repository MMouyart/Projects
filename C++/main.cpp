#include <iostream>
#include "forme.h"
#include"couleur.h"
#include"coords.h"
#include"svgfile.h"
#include"util.h"
#include"styledessin.h"
#include<list>
#include <math.h>
#define PI 3.14159265
#include"lecture.h"

void traitement(std::vector<std::string> test);
void traitement(std::vector<std::string> test);
void ground(Svgfile &svgout)
{
    svgout.addRectangle(0,700,0,800,1000,700,1000,800,"Brown");
}

void mur(Svgfile &svgout)
{
    svgout.addRectangle(0,0,0,800,100,0,100,800,"Brown");
    svgout.addRectangle(900,0,900,800,1000,0,1000,800,"Brown");

}

void dessinerTout(Forme* forme)
{
    Svgfile svgout;
    forme->dessiner(svgout);
}

void CosSin(Svgfile &svgout)  ///Se basant sur le site: http://www.cplusplus.com/reference/cmath/cos/
{
    float param, result;
    param = 60.0;
    result = cos ( param * PI / 180.0 );
    printf ("The cosine of %f degrees is %f.\n", param, result );
    float param2, result2;
    param2 = 30.0;
    result2 = sin (param2*PI/180);
    printf ("The sine of %f degrees is %f.\n", param2, result2 );

    Coords c1= {30,30};
    Coords c2= {80,30};
    Coords c3= {30,50};
    Coords c4= {80,50};

    double angle;
    ///svgout.addRectangle(c1.getX(),c1.getY(),c2.getX(),c2.getY(),c3.getX(),c3.getY(),c4.getX(),c4.getY(),"Brown");
    svgout.addLine(c1.getX(),c1.getY(),c2.getX(),c2.getY(),"Brown");

    double longueur=50;

    std::cout<<"Saisissez l'angle, entre -90 et 90 degres"<<std::endl;
    do
    {
        std::cin>>angle;
    }
    while(angle<-90||angle>90);

    c2.setX(c1.getX()+longueur* cos ( angle * PI / 180.0 ));
    c2.setY(c1.getY()+longueur* sin ( angle * PI / 180.0 ));

    svgout.addLine(c1.getX(),c1.getY(),c2.getX(),c2.getY(),"Brown");

}

int main()
{
    lecture(); /// lecture du fichier
    Svgfile svgout;
    double x=1800; /// coordonées de la salle
    double y=2000;
    std::string id="salle"; ///création de la salle
    std::vector<Forme*> robots;///création du vecteur de robots que contient la salle
    unsigned int i=0; /// compteurs
    int j=0;

    std::string choix; /// choix du nom du robot
    Coords position{0,0}; /// position de la salle
    Forme robot(id,position,x,y,"white",robots);/// création de la salle
    mur(svgout);
    while(i!=5)
    {
        std::cout<<"choisissez votre choix d'action, 1=ajouter un robot\n 2=bouger un robot\n 3=supprimer un robot\n";
        /// choix des actions possibles
        if(i==1)
        {
            ajouter(*robots[j]); ///ajout d'un nouveau robot
            j++;

        }
        if(i==2)
        {
            std::cout<<"rentrez le nom de votre robot svp\n"; ///sélection du nom du robot
            std::cin>>choix;
            while((i<=robots.size())) /// parcours des robots
            {
                if((robots[i]->getID()!=choix)) ///si le nom du robot actuel ne correspond pas à celui du vecteur
                    ++i; ///passage à la case suivante
            }
            if((i==robots.size())&&(robots[i]->getID()!=choix)) ///si on a parcouru tout le vecteur sans trouver le robot choisi on redemande de choisir un nom
            {
                std::cout<<"rentrez le nom de votre robot svp le nom entre n'est pas correct\n";
                std::cin>>choix;
                while((i<=robots.size()))
                {
                    if((robots[i]->getID()!=choix))
                        ++i;
                }
            }
            robots[i]->translation(svgout); ///à la fin des vérifications le robot est translaté
        }
        if(i==3)
        {
            std::cout<<"rentrez le nom de votre robot svp\n";///choix du nomdu robot à supprimer
            std::cin>>choix;
            while((i<=robots.size()))
            {
                if((robots[i]->getID()!=choix)) /// parcours du vecteur
                    ++i;
            }
            if((i==robots.size())&&(robots[i]->getID()!=choix)) /// le vecteur a été parcouru sans trouver le robot choisi
            {
                std::cout<<"rentrez le nom de votre robot svp le nom entre n'est pas correct\n";
                std::cin>>choix;
                while((i<=robots.size()))
                {
                    if((robots[i]->getID()!=choix))
                        ++i;
                }
            }
            robots[i]->~Forme();/// à la fin le robot est supprimé
        }}


    return 0;
}









