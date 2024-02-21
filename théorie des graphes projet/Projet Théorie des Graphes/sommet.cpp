#include <iostream>
#include "sommet.h"
#include <string>
#include <vector>
#include <algorithm>

Sommet::Sommet(int num, char nom, int coordX, int coordY)
{
    m_num = num;
    m_nom=nom;
    m_coordX=coordX;
    m_coordY=coordY;
    m_fiabilite=0;
}


char Sommet::getNom()
{
    return m_nom;
}

int Sommet::getCoordX()
{
    return m_coordX;
}

int Sommet::getCoordY()
{
    return m_coordY;
}



double Sommet::getcentralite()
{
    return m_centralite;
}
void Sommet::centrallitefinal()
{
    m_centralite=m_centralite/3;
}

double Sommet::setcentralite(double cent)
{
    m_centralite=m_centralite+cent;
}
double Sommet::getDegre()
{
    return m_degre;
}


void Sommet::setDegre(double deg)
{
    m_degre=deg;
}


double Sommet::getDegreN()
{
    return m_degreN;
}


void Sommet::setDegreN(double i)
{
    m_degreN = i ;
}


double Sommet::getVectPropre()
{
    return m_VectPropre;
}

void Sommet::setVectPropre(double i)
{
    m_VectPropre = i;
}
