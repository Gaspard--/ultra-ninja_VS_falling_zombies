#include "Player.hpp"
#include "TextureHandler.hpp"

Player::Player(Entity &e, bool canMove)
  : _cooldownDash(0), entity(e), canMove(canMove)
{
  entity.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::BOYAUX);
  entity.renderable.destSize = {0.1, 0.1};
  entity.renderable.sourceSize = {1, 1};
}

void Player::update(void)
{
    _cooldownDash -= (_cooldownDash > 0);
}

void Player::acceleration(int dir)
{
  Vect<2, double> vec(-this->entity.fixture.pos[1], this->entity.fixture.pos[0]);

  this->entity.fixture.speed = (this->entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * dir);
}

void Player::dash(int dir)
{
  Vect<2, double> vec(-this->entity.fixture.pos[1], this->entity.fixture.pos[0]);

  if (entity.isOnPlanet && !_cooldownDash)
  {
    this->entity.fixture.speed += vec.normalized() * (0.01 * (1.0 + entity.isOnPlanet)) * dir;
    _cooldownDash = 15;
  }
}

void Player::jump()
{
  if (this->entity.isOnPlanet)
    this->entity.fixture.speed = this->entity.fixture.speed + this->entity.fixture.pos.normalized() * 0.03;
}

void Player::fastFall()
{
  if (!this->entity.isOnPlanet)
    this->entity.fixture.speed += -(this->entity.fixture.pos.normalized() * 0.04);
}

void Player::getRekt(int dmg)
{
  _hp -= dmg;
}
