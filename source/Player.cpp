#include "Player.hpp"

Player::Player(Entity &e)
  : _e(e)
{
}

void Player::update(void)
{
  _e.update();
}

void Player::setSpeed(Vect<2, double> v)
{
  _e.getFixture().speed = v;
}
