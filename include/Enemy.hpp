#ifndef ENEMY_H_
# define ENEMY_H_

# include <Entity.hpp>

class Enemy
{
protected:
  Entity &_e;

public:
  Enemy(Entity &);
};

#endif /* !ENEMY_H_ */
