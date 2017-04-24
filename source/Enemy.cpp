#include "Enemy.hpp"
#include "Logic.hpp"

Enemy::Enemy(Entity &e, int hp)
  : _hp(hp), entity(e)
{
  _coolDown = 0;
}

bool Enemy::update(const Player& player)
{
  (void)player;
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
  Logic::getInstance().addFlesh(entity);
  Logic::getInstance().addFlesh(entity);
  Logic::getInstance().addFlesh(entity);
}

void Enemy::getRekt(int dmg)
{
  _hp -= dmg;
  _coolDown = 30;
}
