#include "EnemyCommon.hpp"
#include "Logic.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e, 20)
{
  e.fixture.radius = 0.05;
  e.fixture.mass = 15;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
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

void    EnemyCommon::update(const Player& player)
{
  this->Enemy::update(player);
  if (entity.isOnPlanet && !(rand() % 5))
    entity.fixture.speed = entity.fixture.speed + entity.fixture.pos.normalized() * 0.03;
}
