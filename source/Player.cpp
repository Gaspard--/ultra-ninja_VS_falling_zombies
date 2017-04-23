#include "Player.hpp"

Player::Player(Entity &e)
  : _e(e)
{
  _e.renderable.texture = my_opengl::loadTexture("test.bmp");
  _e.renderable.destSize = {0.1, 0.1};
}

void Player::acceleration(int dir)
{
    Vect<2, double> vec(0, 0);

    vec[0] = -this->_e.fixture.speed[1];
    vec[1] = this->_e.fixture.speed[0];
    this->_e.fixture.speed = (this->_e.fixture.speed * 0.8 + vec.normalized() * 0.2) * dir;
}

void Player::jump()
{
    if (this->_e.isOnPlanet)
	    this->_e.fixture.speed = this->_e.fixture.pos.normalized() * 1.5;
}

void Player::fastFall()
{
    if (!this->_e.isOnPlanet)
	    this->_e.fixture.speed = -(this->_e.fixture.pos.normalized() * 1.5);
}
