#include "EnemyShooter.hpp"

EnemyShooter::EnemyShooter(Entity &e)
  : Enemy(e, 15)
{
  e.fixture.radius = 0.02;
  e.fixture.mass = 8;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemyShooter::attack(Player&)
{
  // do nothing
}
