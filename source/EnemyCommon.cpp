#include "EnemyCommon.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e, 20)
{
  e.fixture.radius = 0.05;
  e.fixture.mass = 15;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

EnemyCommon::~EnemyCommon()
{
  // logic.getPlayer().canMove = true;
}

void EnemyCommon::attack(Player& player)
{
  entity.fixture.speed = player.entity.fixture.speed;

  if (player.canMove)
    {
      player.entity.fixture.mass += entity.fixture.mass;
      entity.fixture.mass = player.entity.fixture.mass;
    }

  player.canMove = false;
}

void    EnemyCommon::update(void)
{
  this->Enemy::update();
  if (entity.isOnPlanet && !(rand() % 5))
    entity.fixture.speed = entity.fixture.speed + entity.fixture.pos.normalized() * 0.03;
}
