#include "Logic.hpp"
#include "TextureHandler.hpp"

Bullet::Bullet(Entity &entity)
  : entity(entity), damage(3), lifetime(20)
{
  entity.fixture.mass = 2;
  entity.fixture.radius = 0.01;
  entity.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::BULLET);
  entity.renderable.destSize = {entity.fixture.radius * 2.1, entity.fixture.radius * 2.1};
  entity.renderable.sourceSize = {1, 1};
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
  Player &player = Logic::getInstance().getPlayer();
  Vect<2, double> vec(-entity.fixture.pos[1], entity.fixture.pos[0]);
  Vect<2, double> right(entity.fixture.speed * 0.99 - vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * -1);
  Vect<2, double> left(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * 1);

  if (((right + entity.fixture.pos) - player.entity.fixture.pos).length2() <
      ((left + entity.fixture.pos) - player.entity.fixture.pos).length2())
    entity.fixture.speed = right;
  else
    entity.fixture.speed = left;
}

void Bullet::hit(Enemy &e)
{
  e.getRekt(damage);
  isUseless = true;

    // TODO appliquer le vecteur de la fixture de bullet à la vitesse de l'ennemi
    // TODO enlever des HP à l'Enemy touché.
}
