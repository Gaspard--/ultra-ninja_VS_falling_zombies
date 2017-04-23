#ifndef ENEMY_H_
# define ENEMY_H_

# include "Entity.hpp"

class Enemy
{
protected:
  int _hp;
  Entity &_e;

public:
  Enemy(Entity &, int hp);

  virtual void  update(void) = 0;

  virtual ~Enemy() = default;
};

#endif /* !ENEMY_H_ */
