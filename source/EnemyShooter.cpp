#include "EnemyShooter.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"

EnemyShooter::EnemyShooter(Entity &e)
  : Enemy(e, 15), _cooldown(0)
{
  e.fixture.radius = 0.02;
  e.fixture.mass = 8;
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::TEST);
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
  e.renderable.sourceSize = {1, 1};
}

void EnemyShooter::attack(Player&)
{
  // do nothing
}

bool EnemyShooter::isInRange(Player const& player)
{
  double range = 0.8;

  return (entity.fixture.pos - player.entity.fixture.pos).length2() < CAR(range);
}

void EnemyShooter::shoot()
{
  if (_cooldown > 0)
    return;

  _cooldown = 400;

  Logic &logic = Logic::getInstance();

  logic.addBullet(entity.fixture.pos);
  logic.addBullet(entity.fixture.pos);
}

bool EnemyShooter::update(const Player& player)
{
  _cooldown -= (_cooldown > 0);

  Vect<2, double> vec(-entity.fixture.pos[1], entity.fixture.pos[0]);
  Vect<2, double> right(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * -1);
  Vect<2, double> left(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)));

  if (((right + entity.fixture.pos) - player.entity.fixture.pos).length2() <
      ((left + entity.fixture.pos) - player.entity.fixture.pos).length2())
    (_cooldown == 0) ? entity.fixture.speed = right : entity.fixture.speed = left;
  else
    (_cooldown == 0) ? entity.fixture.speed = left : entity.fixture.speed = right;

  if (_cooldown != 0)
    entity.fixture.speed *= 0.7;

  if (!entity.isOnPlanet)
    entity.fixture.speed = -(entity.fixture.pos.normalized() * 0.01);

  return this->Enemy::update(player);
}
