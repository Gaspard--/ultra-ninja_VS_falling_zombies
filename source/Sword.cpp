#include "Sword.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"

Sword::Sword(Entity &entity, Vect<2u, double> knockback)
  : entity(entity), damage(10), lifetime(6), knockback(knockback)
{
  entity.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::SWORDRADIUS);
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

void	Sword::hit(Enemy &e, Player &p)
{
  if (!p.entity.isOnPlanet)
  {
    Logic::getInstance().incCombo();
    Logic::getInstance().addToScore(1);
  }
  e.entity.fixture.speed += knockback * 0.1;
  if (lifetime != 1)
    return ;
  e.entity.fixture.speed += knockback * 0.9;
  p.entity.fixture.speed -= knockback * 0.3;
  e.getRekt(damage);
}

void	Sword::hit(Bullet &e, Player &p)
{
  if (!p.entity.isOnPlanet)
    {
      Logic::getInstance().incCombo();
      Logic::getInstance().addToScore(1);
    }
  if (lifetime != 0)
    return ;
  e.isUseless = true;
  e.entity.isUseless = true;
}
