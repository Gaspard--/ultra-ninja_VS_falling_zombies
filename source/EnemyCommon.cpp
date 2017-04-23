#include "EnemyCommon.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e, 20)
{
  e.fixture.radius = 0.05;
  e.fixture.mass = 30;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

EnemyCommon::~EnemyCommon()
{
  // logic.getPlayer().canMove = true;
}

void EnemyCommon::attack(Player& player)
{
  _e.fixture.speed = player.entity.fixture.speed;

  player.entity.fixture.mass += _e.fixture.mass;
  _e.fixture.mass = player.entity.fixture.mass;

  player.canMove = false;
}
