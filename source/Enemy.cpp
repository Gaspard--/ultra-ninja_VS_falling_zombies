#include "Enemy.hpp"

Enemy::Enemy(Entity &e, int hp)
  : _hp(hp), entity(e)
{
}

Enemy::~Enemy()
{
}

void Enemy::getRekt(int dmg)
{
  _hp -= dmg;
}
