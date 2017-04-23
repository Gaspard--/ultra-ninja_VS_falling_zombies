#include "EnemyShooter.hpp"
#include "Logic.hpp"

EnemyShooter::EnemyShooter(Entity &e)
  : Enemy(e, 15)
{
  e.fixture.radius = 0.02;
  e.fixture.mass = 8;
  e.renderable.texture = my_opengl::loadTexture("resources/bite.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
  e.renderable.sourceSize = {1, 1};
}

void EnemyShooter::attack(Player&)
{
  // do nothing
}

void EnemyShooter::shoot()
{
  // TODO if (within attack range) -> attack
  // target : player
  Player& player = Logic::getInstance().getPlayer();

  // TODO actual shoot
}
