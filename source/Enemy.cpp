#include <cmath>
#include "Enemy.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"

Enemy::Enemy(Entity &e, int hp)
  : _hp(hp), entity(e)
{
  _coolDown = 0;
  _animation = 0;
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::ZOMBIE);
  e.renderable.sourceSize = {0.5, 1};
}

void Enemy::animate()
{
  if (!entity.isOnPlanet) {
    entity.renderable.sourcePos = {0.5, 0};
  }

  if (entity.isOnPlanet && ++_animation >= 10)
    {
      if (entity.renderable.sourcePos[0] == 0)
	entity.renderable.sourcePos = {0.5, 0};
      else
	entity.renderable.sourcePos = {0.0, 0};
      _animation = 0;
    }
}

bool Enemy::update(const Player&)
{
  animate();

  isUseless = _hp <= 0;
  entity.isUseless = isUseless;
  if (isUseless)
    onDeath();
  if (_coolDown)
    {
      --_coolDown;
      return (false);
    }
  return (true);
}

void Enemy::onDeath()
{
  Logic::getInstance().incCombo();
  Logic::getInstance().addToScore(10);
  for (unsigned int i(0); i < 20; ++i)
    {
      Vect<2u, float> dir(std::cos(i), std::sin(i));

      Logic::getInstance().addFlesh(entity, [dir](Entity &e)
				    {
				      double size(0.4 * (rand() % 3 + 2));

				      e.renderable.sourceSize = {1, 1};
				      e.renderable.sourcePos = {0, 0};
				      e.renderable.destSize *= size;
				      e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::BOYAUX);
				      e.fixture.radius *= size;
				      e.fixture.speed += dir * (0.02 * (rand() % 3 + 1)) * size;
				      e.fixture.mass = 100;
				    }, true);
    }
  Logic::getInstance().addFlesh(entity, [](Entity &e)
				{
				  e.renderable.sourceSize[1] *= 0.5;
				  e.renderable.destSize[1] *= 0.5;
				  e.fixture.speed -= e.fixture.pos.normalized() * 0.1;
				  e.fixture.radius *= 0.5;
				  e.fixture.mass = 100;
				}, false);
  Logic::getInstance().addFlesh(entity, [](Entity &e)
				{
				  e.renderable.sourcePos[1] += e.renderable.sourceSize[1] * 0.5;
				  e.renderable.sourceSize[1] *= 0.5;
				  e.renderable.destSize[1] *= 0.5;
				  e.fixture.pos[1] += e.renderable.destSize[1] * 0.5;
				  e.fixture.speed += e.fixture.pos.normalized() * 0.1;
				  e.fixture.radius *= 0.5;
				  e.fixture.mass = 100;
				}, false);
}

void Enemy::getRekt(int dmg)
{
  _hp -= dmg;
  _coolDown = 30;
}
