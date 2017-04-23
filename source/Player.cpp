#include "Player.hpp"

Player::Player(Entity &e)
  : _e(e)
{
  _e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  _e.renderable.destSize = {0.1, 0.1};
}

void Player::acceleration(int dir)
{
  Vect<2, double> vec(-this->_e.fixture.pos[1], this->_e.fixture.pos[0]);

  this->_e.fixture.speed = (this->_e.fixture.speed * 0.99 + vec.normalized() * 0.001 * dir);
}

void Player::jump()
{
    if (this->_e.isOnPlanet)
      this->_e.fixture.speed = this->_e.fixture.speed + this->_e.fixture.pos.normalized() * 0.03;
}

void Player::fastFall()
{
    if (!this->_e.isOnPlanet)
      this->_e.fixture.speed = -(this->_e.fixture.pos.normalized() * 0.06);
}
