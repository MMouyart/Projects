#ifndef FORME_H_INCLUDED
#define FORME_H_INCLUDED
#include<iostream>
#include<list>
#include<string>
#include<vector>
#include"coords.h"
#include"couleur.h"
#include"styledessin.h"
#include"svgfile.h"
#include"util.h"


class Forme
{
private:
std::string m_id; ///nom de la forme
Coords m_position; ///position de la forme
Coords m_ancrage; /// coordonnées de l'ancrage de la forme
double m_largeur; ///largeur de la forme
double m_longueur; ///longueur de la forme
std::string m_color; ///couleur de la forme
std::vector<Forme*> m_membre; /// vecteur des membres de la forme
public:
    Forme(std::string id,Coords position,double largeur, double longueur, std::string coul,std::vector<Forme*> membre);///constructeur par paramètres
    Forme();/// constructeur par défaut
    ~Forme();/// destructeur par défaut
    void dessiner(Svgfile &svgout); /// dessin de la forme
    Coords getPosition() const; /// acquisition des coordonnées
    double getLargeur() const; ///acquisition de la largeur
    double getLongueur() const;/// acquisition de la longueur
    std::string getID() const;/// acquisition du nom
    void translation(Svgfile &svgout); ///translation de la forme
    void translation2(double x,Svgfile &svgout);
    void rotation(Svgfile &svgout); ///faut le faire
    void gravite(double y,Svgfile &svgout); ///activation de la gravité
    Coords setTL(); /// méthodes pour activer les points d'ancrages de la forme
    Coords setTC();
    Coords setTR();
    Coords setML();
    Coords setMC();
    Coords setMR();
    Coords setBL();
    Coords setBC();
    Coords setBR();

};

void ajouter(Forme Robot);/// ajout d'un robot donc d'une forme


#endif // FORME_H_INCLUDED
