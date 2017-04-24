#include "EnemySmall.hpp"
#include "TextureHandler.hpp"

EnemySmall::EnemySmall(Entity &e)
  : Enemy(e, 10), _attackDist(0.2)
{
  _dir = ((rand() % 2) * 2) - 1;
  _dash = false;
  e.fixture.radius = 0.03;
  e.fixture.mass = 20;
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::TEST);
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemySmall::attack(Player& player)
{
  Vect<2, double> vec(-player.entity.fixture.pos[1], player.entity.fixture.pos[0]);
  player.entity.fixture.speed = entity.fixture.speed * 3;

  entity.fixture.speed = entity.fixture.speed * -1.5;
  _coolDown = 40;
  _dash = false;
  player.getRekt(1);
}

bool    EnemySmall::update(const Player& player)
{
  Vect<2, double> vec(-entity.fixture.pos[1], entity.fixture.pos[0]);
  Vect<2, double> right(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (6.0 + entity.isOnPlanet)) * -1);
  Vect<2, double> left(entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (6.0 + entity.isOnPlanet)) * 1);

  if (this->Enemy::update(player) && (entity.isOnPlanet || _dash))
    {
      _dash = true;
      entity.fixture.speed = (entity.fixture.speed * 0.99 + vec.normalized() * (0.0005 * (0.05 + entity.isOnPlanet)) * _dir);
      if (((right + entity.fixture.pos) - player.entity.fixture.pos).length2() < _attackDist &&
          ((left + entity.fixture.pos) - player.entity.fixture.pos).length2() > ((right + entity.fixture.pos) - player.entity.fixture.pos).length2())
        entity.fixture.speed = right;
      else if (((left + entity.fixture.pos) - player.entity.fixture.pos).length2() < _attackDist)
        entity.fixture.speed = left;
      else
        _dash = false;
    }
  return (false);
}
