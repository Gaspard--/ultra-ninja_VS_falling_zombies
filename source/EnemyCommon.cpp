#include "EnemyCommon.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e)
{
  _e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  _e.renderable.destSize = {0.4, 0.4};
}
