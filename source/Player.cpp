#include "Player.hpp"

Player::Player(Entity &e)
  : _e(e)
{
}

void Player::update(void)
{
  _e.update();
}
