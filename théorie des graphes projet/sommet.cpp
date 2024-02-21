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


int Sommet::getDegre()
{
    return m_degre;
}


void Sommet::setDegre(int deg)
{
    m_degre=deg;
}


float Sommet::getDegreN()
{
    return m_degreN;
}


void Sommet::setDegreN(float i)
{
    m_degreN = i ;
}

float Sommet::getCentralite()
{
    return centralite;
}

void Sommet::setCentralite(float centralPRox, float centralInter)
{
    centralite=(m_degreN*0.2+m_VectPropre*0.5+centralInter+centralPRox*0.8)/4;

}


float Sommet::getVectPropre()
{
    return m_VectPropre;
}

void Sommet::setVectPropre(float i)
{
    m_VectPropre = i;
}


void Sommet::suppSuccesseur(Sommet* sommet)
{
    m_successeurs.erase(m_successeurs.begin() + sommet->getNum() - 1);
}


