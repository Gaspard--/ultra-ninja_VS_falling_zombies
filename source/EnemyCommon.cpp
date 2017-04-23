#include "EnemyCommon.hpp"
#include "Logic.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e, 20), _isAttached(false)
{
  e.fixture.radius = 0.05;
  e.fixture.mass = 15;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemyCommon::onDeath()
{
  EnemyCommon::onDeath();
  if (_isAttached)
    Logic::getInstance().getPlayer().canMove = true;
}

void EnemyCommon::attack(Player& player)
{
  entity.fixture.speed = player.entity.fixture.speed;

  if (player.canMove)
    {
      player.entity.fixture.mass += entity.fixture.mass;
      entity.fixture.mass = player.entity.fixture.mass;
      _isAttached = true;
    }

  player.canMove = false;
}

void    EnemyCommon::update(void)
{
  if (entity.isOnPlanet && !(rand() % 5))
    entity.fixture.speed = entity.fixture.speed + entity.fixture.pos.normalized() * 0.03;
}
