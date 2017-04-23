#include "Enemy.hpp"

Enemy::Enemy(Entity &e)
  : _e(e)
{
}

void Enemy::update(void)
{
  _e.update();
}
