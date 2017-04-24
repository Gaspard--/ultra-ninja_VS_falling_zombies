#include "Bullet.hpp"
#include "TextureHandler.hpp"

Bullet::Bullet(Entity &entity, Vect<2u, double> knockback)
  : entity(entity), damage(3), lifetime(20), knockback(knockback)
{
  entity.fixture.mass = 0;
  entity.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::BULLET);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
  --lifetime;
  isUseless = lifetime <= 0;
  entity.isUseless = isUseless;
}

void Bullet::hit(Enemy &e)
{
  e.entity.fixture.speed += knockback;
  e.getRekt(damage);
  isUseless = true;

  // is useless after hit
  isUseless = true;

    // TODO appliquer le vecteur de la fixture de bullet à la vitesse de l'ennemi
    // TODO enlever des HP à l'Enemy touché.
}
