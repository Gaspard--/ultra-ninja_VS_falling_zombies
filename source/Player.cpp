#include "Player.hpp"

Player::Player(Entity &e)
  : _e(e)
{
}

void Player::update(void)
{
  _e.update();
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
    this->_e.fixture.speed = this->_e.fixture.speed.normalized() * 1.5;
}
