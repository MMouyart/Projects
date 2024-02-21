#include "coords.h"
#include <iostream>

Coords::Coords(double x, double y) ///constructeur de coordonn�es � partir de points s�lectionn�s
    : m_x{x}, m_y{y}
{ }

Coords::Coords() ///constructeur par d�faut
    : m_x{0}, m_y{0}
{ }

void Coords::afficher() const ///affichage des coordonn�es
{
    std::cout << "(" << m_x << ", " << m_y << ")";
}



double Coords::getX() const///acquisition de la coordonn�e en x
{
    return m_x;
}

double Coords::getY() const ///acquisition de la coordonn�e en y
{
    return m_y;
}

/// Somme vectorielle (version courte)
Coords operator+(const Coords& c1, const Coords& c2)
{
    return {c1.m_x + c2.m_x, c1.m_y + c2.m_y  };
}

void Coords::ajouter_x_y(double x, double y)
{
    m_x=m_x+x;
    m_y=m_y+y;
}
void Coords::setX(double x)
{
    m_x=x;
}
void Coords::setY(double y)
{
    m_y=y;
}
