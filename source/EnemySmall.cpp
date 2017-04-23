#include "EnemySmall.hpp"

EnemySmall::EnemySmall(Entity &e)
  : Enemy(e, 10)
{
  e.fixture.radius = 0.03;
  e.fixture.mass = 37;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}
