#include "Player.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"
#include "SoundHandler.hpp"

Player::Player(Entity &e, bool canMove)
  : _cooldownDash(0), entity(e), canMove(canMove)
{
  entity.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::PLAYER);
  entity.renderable.destSize = {0.1, 0.1};
  entity.renderable.sourceSize = {0.5, 1};
  _animation = 0;
  _maxAnimationFrame = 10;
}

void Player::animate()
{
  if (!entity.isOnPlanet) {
    entity.renderable.sourcePos = {0.5, 0};
  }

  if (entity.fixture.speed[0] <= 0.0035 && entity.fixture.speed[0] >= -0.0035 &&
      entity.fixture.speed[1] <= 0.0035 && entity.fixture.speed[1] >= -0.0035)
    {
      entity.renderable.sourcePos = {0.0, 0};
      return;
    }

  if (entity.isOnPlanet && ++_animation >= _maxAnimationFrame)
    {
      if (entity.renderable.sourcePos[0] == 0)
	entity.renderable.sourcePos = {0.5, 0};
      else
	entity.renderable.sourcePos = {0.0, 0};
      _animation = 0;
    }
}

void Player::update(void)
{
  animate();

  _cooldownDash -= (_cooldownDash > 0);
  if (entity.isOnPlanet)
    Logic::getInstance().resetCombo();
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
    SoundHandler::getInstance().playSound(SoundHandler::DASH);
  }
}

void Player::jump()
{
  if (this->entity.isOnPlanet)
    {
      this->entity.fixture.speed = this->entity.fixture.speed + this->entity.fixture.pos.normalized() * 0.03;
      playRandomPlayerSound();
    }
}

void Player::fastFall()
{
  if (!this->entity.isOnPlanet)
    {
      this->entity.fixture.speed += -(this->entity.fixture.pos.normalized() * 0.04);
      playRandomPlayerSound();
    }
}

void Player::getRekt(int dmg)
{
  _hp -= dmg;
}

void Player::playRandomPlayerSound()
{
  SoundHandler &sh = SoundHandler::getInstance();
  sh.playSound(sh.player_sounds[rand() % sh.player_sounds.size()], 50);
}
