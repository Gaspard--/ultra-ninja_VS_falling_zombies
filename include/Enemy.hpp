#ifndef ENEMY_H_
# define ENEMY_H_

# include "Entity.hpp"

class Player;

class Enemy
{
protected:
  int _hp;

public:
  virtual void attack(Player& player) = 0;

public:
  Enemy(Entity &, int hp);
  virtual ~Enemy();

  Entity &entity;
};

#endif /* !ENEMY_H_ */
