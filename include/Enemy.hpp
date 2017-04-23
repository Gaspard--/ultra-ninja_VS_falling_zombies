#ifndef ENEMY_H_
# define ENEMY_H_

# include "Entity.hpp"

class Enemy
{
protected:
  int _hp;

public:
  Enemy(Entity &, int hp);
  virtual ~Enemy() = default;

  Entity &entity;
};

#endif /* !ENEMY_H_ */
