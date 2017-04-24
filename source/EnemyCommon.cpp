#include "EnemyCommon.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e, 20)
{
  e.fixture.radius = 0.05;
  e.fixture.mass = 15;
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::TEST);
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemyCommon::attack(Player& player)
{
  Vect<2, double> pos = player.entity.fixture.pos;
  Vect<2, double> perp = {pos[1], -pos[0]};
  Vect<2, double> diff = (pos - entity.fixture.pos);
  double scl = perp.scalar(diff);

  Vect<2, double> vec(-player.entity.fixture.pos[1], player.entity.fixture.pos[0]);
  player.entity.fixture.speed = (vec.normalized() * 0.01)
    * -((0.0 < scl) - (scl < 0.0))
    + (entity.fixture.pos.normalized() * 0.05);


  entity.fixture.speed = entity.fixture.speed * 0.5
    - entity.fixture.pos.normalized() * 0.09 * 0.2;
  player.getRekt(2);
}

bool    EnemyCommon::update(const Player& player)
{
  Vect<2, double> vec(-entity.fixture.pos[1], entity.fixture.pos[0]);
  Vect<2, double> right(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * -1);
  Vect<2, double> left(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * 1);

  if (this->Enemy::update(player) && entity.isOnPlanet)
    {
      if (((right + entity.fixture.pos) - player.entity.fixture.pos).length2() <
          ((left + entity.fixture.pos) - player.entity.fixture.pos).length2())
        entity.fixture.speed = right;
      else
        entity.fixture.speed = left;
      if (!(rand() % (int)(10000 * ((entity.fixture.speed + entity.fixture.pos).normalized() - player.entity.fixture.pos.normalized()).length2() + 1)))
        entity.fixture.speed = entity.fixture.speed + entity.fixture.pos.normalized() * 0.03;
    }
  return (false);
}
