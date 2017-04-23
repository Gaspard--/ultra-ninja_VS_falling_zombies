#include "Sword.hpp"

Sword::Sword(Vect<2, double> pos, Vect<2, double> speed, double radius)
: entity({pos, speed, radius, 0}), damage(3)
{
}

Sword::~Sword()
{
}

void	Sword::Hit(Enemy const & e) const
{
    // TODO appliquer le vecteur de la fixture de sword à la vitesse de l'ennemi

    // TODO enlever des HP à l'Enemy touché.
}
