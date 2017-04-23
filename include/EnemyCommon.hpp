#ifndef ENEMYCOMMON_H_
# define ENEMYCOMMON_H_

# include "Enemy.hpp"

class EnemyCommon : public Enemy
{
private:

public:
  void attack(Player& player) override;

public:
  EnemyCommon(Entity &);
  void  update(void);
};

#endif /* !ENEMYCOMMON_H_ */
