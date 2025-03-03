#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED


class Coords
{
    public :
        Coords(double x, double y);
        Coords();

        void afficher() const;

        double getX() const;
        double getY() const;

        void ajouter_x_y(double x, double y);
        void setX(double x);
        void setY(double y);
        friend Coords operator+(const Coords& c1, const Coords& c2);

    private :
        double m_x;
        double m_y;
};


#endif // COORDS_H_INCLUDED
