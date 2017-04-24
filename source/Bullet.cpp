#include "Logic.hpp"
#include "TextureHandler.hpp"

Bullet::Bullet(Entity &entity)
  : entity(entity), damage(3), lifetime(20)
{
  entity.fixture.mass = 5;
  entity.fixture.radius = 0.025;
  entity.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::BULLET);
  entity.renderable.destSize = {entity.fixture.radius * 2.1, entity.fixture.radius * 2.1};
  entity.renderable.sourceSize = {1, 1};
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
  if (_lock)
    {
      entity.fixture.speed *= 1.01;
      if (--lifetime < 0)
	{
	  isUseless = true;
	  entity.isUseless = true;
	}
      return;
    }

  Player &player = Logic::getInstance().getPlayer();
  Vect<2, double> diff(player.entity.fixture.pos - entity.fixture.pos);

  if (diff.length2() < CAR(0.8))
    {
      entity.fixture.speed = diff * 0.08;
      if (up == 0)
	_lock = true;
    }
  else
    {
      Vect<2, double> vec(-entity.fixture.pos[1], entity.fixture.pos[0]);
      Vect<2, double> right(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * -1);
      Vect<2, double> left(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (1.0 + entity.isOnPlanet)) * 1);

      if (((right + entity.fixture.pos) - player.entity.fixture.pos).length2() <
	  ((left + entity.fixture.pos) - player.entity.fixture.pos).length2())
	entity.fixture.speed = right;
      else
	entity.fixture.speed = left;
    }

  if (--up >= 0)
    entity.fixture.speed = entity.fixture.speed + entity.fixture.pos.normalized() * 0.05;
}

void Bullet::hit(Player &player)
{
  player.getRekt(damage);
  isUseless = true;
  entity.isUseless = true;
  player.entity.fixture.speed = entity.fixture.speed * 3;
  // TODO EXPLOSION
}
