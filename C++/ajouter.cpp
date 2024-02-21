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
void ajouter(Forme Robot) ///méthode d'ajout d'un robot
{
    double x=0; /// déclarations des variables
    double y=500;
    std::string id;
    double dx=0,dy=0;
    std::string color;
    std::cout<<"rentrez le nom de votre robot"<<id<<std::endl; /// choix du nom
    std::vector<Forme*> membre;/// création des membres
    std::cout<<"rentrez la coordonnee en X"<<x<<std::endl; ///choix des coordonnées
    std::cout<<"rentrez la coordonnee en Y"<<y<<std::endl;
    Coords position{x,y};///création des coordonnées
    std::cout<<"rentrez le deplacement en X"<<dx<<std::endl;///choix des déplacements
    std::cout<<"rentrez le deplacement en Y"<<dy<<std::endl;
    std::cout<<"rentrez la couleur en lettres svp"<<color<<std::endl;///choix de la couleur
    Forme robot(id,position,dx,dy,color,membre);/// création du robot

}
