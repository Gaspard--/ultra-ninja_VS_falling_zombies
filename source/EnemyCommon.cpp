#include "EnemyCommon.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e)
{
  _e.renderable.texture = my_opengl::loadTexture("test.bmp");
  _e.renderable.destSize = {0.2, 0.2};
}
