#include "EnemyShooter.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"

EnemyShooter::EnemyShooter(Entity &e)
  : Enemy(e, 15)
{
  e.fixture.radius = 0.02;
  e.fixture.mass = 8;
  // FIXME: REPLACE BULLET BY TEST or SHOOTER TEXTURE
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::BULLET);
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
  e.renderable.sourceSize = {1, 1};
}

void EnemyShooter::attack(Player&)
{
  // do nothing
}

void EnemyShooter::shoot()
{
  // TODO if (within attack range) -> attack
  // target : player
  Player& player = Logic::getInstance().getPlayer();

  // TODO actual shoot
}

void EnemyShooter::update(const Player& player)
{
  Vect<2, double> vec(-entity.fixture.pos[1], entity.fixture.pos[0]);
  Vect<2, double> right(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * -1);
  Vect<2, double> left(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * 1);

  if (((right + entity.fixture.pos) - player.entity.fixture.pos).length2() <
      ((left + entity.fixture.pos) - player.entity.fixture.pos).length2())
    entity.fixture.speed = right;
  else
    entity.fixture.speed = left;
  if (!(rand() % (int)(10000 * ((entity.fixture.speed + entity.fixture.pos).normalized() - player.entity.fixture.pos.normalized()).length2() + 1)))
    entity.fixture.speed = -(entity.fixture.pos.normalized() * 0.06);

  this->Enemy::update(player);
}
