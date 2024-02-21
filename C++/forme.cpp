#include<iostream>
#include<string>
#include<vector>
#include"coords.h"
#include"couleur.h"
#include"forme.h"
#include"styledessin.h"
#include"svgfile.h"
#include"util.h"
#include<windows.h>

Forme::Forme(std::string id,Coords position,double largeur, double longueur, std::string coul,std::vector<Forme*> membre):m_id{id}, m_position {position},m_largeur{largeur},m_longueur{longueur},m_color {coul},
             m_membre{membre}

{};
Forme::~Forme()
{};
std::string Forme::getID() const
{
    std::string buffer;
    buffer=m_id;
    return buffer;
}
void Forme::dessiner(Svgfile &svgout)
{
    svgout.addRectangle(m_position.getX(),m_position.getY(),
                        m_position.getX(),m_position.getY()+m_largeur,
                        m_position.getX()+m_longueur,m_position.getY(),
                        m_position.getX()+m_longueur,m_position.getY()+m_largeur,
                        m_color);
}

Coords Forme::getPosition() const
{
    return m_position;
}

double Forme::getLargeur() const
{
    return m_largeur;
}

double Forme::getLongueur() const
{
    return m_longueur;
}
Forme::Forme():m_id{" "},m_position{},m_largeur{0},m_longueur{0},m_color{" "},m_membre{NULL}
{

}

void Forme::translation(Svgfile &svgout)
{
    double x;
   std::cout<<"Saisir translation"<<std::endl; ///choix du déplacement du robot
   std::cin>>x;
   if(m_position.getX()<x) /// si la position est inférieure au choix de la case, on incrémente les coordonnées en x
   {
      while(m_position.getX()<x)
      {
          m_position.setX(m_position.getX()+1);
      }
   }

    if(m_position.getX()>x) /// si la position est supérieure au choix de la case, on décrémente les coordonnées en x
   {
      while(m_position.getX()<x)
      {
          m_position.setX(m_position.getX()-1);
      }
   }
   if(m_position.getX()==x)
   {
       ///on deplace pas
   }

}

void Forme::translation2(double x,Svgfile &svgout)
{
    std::cout<<"Saisir translation+"<<std::endl;
   std::cin>>x;
   if(x>0)
   {
       for(int i=0;i<x;++i)
       {
           m_position.setX(m_position.getX()+1);
       }
   }

   if(x<0)
   {
       int y=-x;
       for(int i=0;i<y;++i)
       {
           m_position.setX(m_position.getX()-1);
       }
   }

   if(x==0)
   {
       ///on deplace pas
   }
}

void Forme::gravite(double y,Svgfile &svgout) ///gravité pour les robots
{
    while(m_position.getY()+m_largeur<700) ///tant que le robot se trouve au dessus du sol sans le toucher on le fait descendre d'une case
    {
    m_position.setY(m_position.getY()+1);
    }
}

Coords Forme::setTL() /// création du point d'ancrage haut gauche
{
m_ancrage.setX(m_position.getX());
m_ancrage.setY(m_position.getY());
   return m_ancrage;
}

Coords Forme::setTC() /// création du point d'ancrage haut milieu
{
m_ancrage.setX(m_position.getX()+(m_longueur/2));
m_ancrage.setY(m_position.getY());
   return m_ancrage;
}

Coords Forme::setTR() /// création du point d'ancrage haut droit
{
m_ancrage.setX(m_position.getX()+m_longueur);
m_ancrage.setY(m_position.getY());
   return m_ancrage;
}

Coords Forme::setML() /// création du point d'ancrage milieu gauche
{
m_ancrage=m_position;
m_ancrage.setX(m_position.getX());
m_ancrage.setY(m_position.getY()+(m_largeur/2));
   return m_ancrage;
}

Coords Forme::setMC()/// création du point d'ancrage milieu milieu
{
m_ancrage=m_position;
m_ancrage.setX(m_position.getX()+(m_longueur/2));
m_ancrage.setY(m_position.getY()+(m_largeur/2));
   return m_ancrage;
}

Coords Forme::setMR() /// création du point d'ancrage milieu droite
{
m_ancrage=m_position;
m_ancrage.setX(m_position.getX()+m_longueur);
m_ancrage.setY(m_position.getY()+(m_largeur/2));
   return m_ancrage;
}

Coords Forme::setBL() /// création du point d'ancrage bas gauche
{
m_ancrage=m_position;
m_ancrage.setX(m_position.getX());
m_ancrage.setY(m_position.getY()+m_largeur);
   return m_ancrage;
}

Coords Forme::setBC() /// création du point d'ancrage bas centre
{
m_ancrage=m_position;
m_ancrage.setX(m_position.getX()+(m_longueur/2));
m_ancrage.setY(m_position.getY()+m_largeur);
   return m_ancrage;
}

Coords Forme::setBR() /// création du point d'ancrage bas droite
{m_ancrage=m_position;
m_ancrage.setX(m_position.getX()+m_longueur);
m_ancrage.setY(m_position.getY()+m_largeur);
   return m_ancrage;
}


