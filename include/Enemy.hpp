#ifndef ENEMY_H_
# define ENEMY_H_

# include "Entity.hpp"
# include "Player.hpp"

class Enemy
{
protected:
  int _hp;

public:
  virtual void attack(Player& player) = 0;

public:
  Enemy(Entity &, int hp);

  virtual void  update(void) = 0;

  virtual ~Enemy() = default;

  void getRekt(int);

  Entity &entity;
};

#endif /* !ENEMY_H_ */
