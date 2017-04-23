#include "EnemyLarge.hpp"

EnemyLarge::EnemyLarge(Entity &e)
  : Enemy(e, 30)
{
  e.fixture.radius = 0.1;
  e.fixture.mass = 50;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}
