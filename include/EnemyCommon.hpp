#ifndef ENEMYCOMMON_H_
# define ENEMYCOMMON_H_

# include "Enemy.hpp"

class EnemyCommon : public Enemy
{
private:
  bool _isAttached;

public:
  void attack(Player& player) override;

public:
  EnemyCommon(Entity &);
  ~EnemyCommon();
  void  update(void) override;
};

#endif /* !ENEMYCOMMON_H_ */
