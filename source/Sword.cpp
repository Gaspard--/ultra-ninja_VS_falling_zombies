#include "Sword.hpp"

Sword::Sword(Entity &entity, Vect<2u, double> knockback)
  : entity(entity), damage(3), lifetime(6), knockback(knockback)
{
    entity.renderable.texture = my_opengl::loadTexture("resources/swordRadius.bmp");
    entity.renderable.destSize = {entity.fixture.radius * 2.0, entity.fixture.radius * 2.0};
    entity.renderable.sourceSize = {1, 1};
}

Sword::~Sword()
{
}

void Sword::update()
{
  lifetime -= 1;
  isUseless = lifetime <= 0;
  entity.isUseless = isUseless;
}

void	Sword::hit(Enemy &e)
{
  e.entity.fixture.speed += knockback;
  e.getRekt(damage);

    // TODO appliquer le vecteur de la fixture de sword à la vitesse de l'ennemi
    // TODO enlever des HP à l'Enemy touché.
}
