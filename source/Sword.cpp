#include "Sword.hpp"

Sword::Sword(Entity &entity, Vect<2u, double> knockback)
  : entity(entity), damage(3), knockback(knockback)
{
}

Sword::~Sword()
{
}

void	Sword::Hit(Enemy &e)
{
  e.entity.fixture.speed += knockback;
  e.getRect(damage);
    // TODO appliquer le vecteur de la fixture de sword à la vitesse de l'ennemi

    // TODO enlever des HP à l'Enemy touché.
}
