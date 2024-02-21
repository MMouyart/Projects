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

int Sommet::getNum()
{
    return m_num;
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
int Sommet::getdegre()
 {int i=0;
        int deg;
        for(i=0;i<m_successeurs.size();++i)
        {
            deg++;
        }
            return deg;
        };




