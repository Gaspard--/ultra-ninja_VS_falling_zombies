#include <iostream>
#include "EnemyLarge.hpp"
#include "Player.hpp"

EnemyLarge::EnemyLarge(Entity &e)
  : Enemy(e, 30)
{
  e.fixture.radius = 0.1;
  e.fixture.mass = 10;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemyLarge::attack(Player& player)
{
  Vect<2, double> pos = player.entity.fixture.pos;
  Vect<2, double> perp = {pos[1], -pos[0]};
  Vect<2, double> diff = (pos - entity.fixture.pos);
  double scl = perp.scalar(diff);

  Vect<2, double> vec(-player.entity.fixture.pos[1], player.entity.fixture.pos[0]);
  player.entity.fixture.speed = (vec.normalized() * 0.016)
    * -((0.f < scl) - (scl < 0.f))
    - (this->entity.fixture.pos.normalized() * 0.06);


  entity.fixture.speed = entity.fixture.speed * 0.5
    + entity.fixture.pos.normalized() * 0.09 * 0.2;
  player.getRekt(2);
}

void    EnemyLarge::update(void)
{
}
