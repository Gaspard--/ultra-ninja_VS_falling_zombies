#include "Player.hpp"

Player::Player(Entity &e)
  : _e(e)
{
  _e.renderable.texture = my_opengl::loadTexture("test.bmp");
  _e.renderable.destSize = {0.1, 0.1};
}
