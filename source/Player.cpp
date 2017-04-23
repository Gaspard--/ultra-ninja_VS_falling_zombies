#include "Player.hpp"

Player::Player(Entity &e)
  : entity(e)
{
  entity.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  entity.renderable.destSize = {0.1, 0.1};
}

void Player::acceleration(int dir)
{
  Vect<2, double> vec(-this->entity.fixture.pos[1], this->entity.fixture.pos[0]);

  this->entity.fixture.speed = (this->entity.fixture.speed * 0.99 + vec.normalized() * 0.001 * dir);
}

void Player::jump()
{
  if (this->entity.isOnPlanet)
    this->entity.fixture.speed = this->entity.fixture.speed + this->entity.fixture.pos.normalized() * 0.03;
}

void Player::fastFall()
{
    if (!this->entity.isOnPlanet)
      this->entity.fixture.speed = -(this->entity.fixture.pos.normalized() * 0.06);
}

void Player::getRekt(int dmg)
{
  _hp -= dmg;
}
