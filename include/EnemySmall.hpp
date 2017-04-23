#ifndef ENEMYSMALL_H_
# define ENEMYSMALL_H_

# include "Enemy.hpp"

class EnemySmall : public Enemy
{
private:

public:
  EnemySmall(Entity &);
  void  update(void);
};

#endif /* !ENEMYSMALL_H_ */
