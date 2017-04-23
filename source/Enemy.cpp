#include "Enemy.hpp"
#include "Logic.hpp"

Enemy::Enemy(Entity &e, int hp)
  : _hp(hp), entity(e)
{
}

void Enemy::update()
{
  isUseless = _hp <= 0;
  entity.isUseless = isUseless;
  if (isUseless)
    onDeath();
}

void Enemy::onDeath()
{
  Logic::getInstance().addFlesh(entity);
  Logic::getInstance().addFlesh(entity);
  Logic::getInstance().addFlesh(entity);
}

void Enemy::getRekt(int dmg)
{
  _hp -= dmg;
}
