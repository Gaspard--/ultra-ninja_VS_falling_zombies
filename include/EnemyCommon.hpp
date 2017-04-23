#ifndef ENEMYCOMMON_H_
# define ENEMYCOMMON_H_

# include "Enemy.hpp"

class EnemyCommon : public Enemy
{
private:
  bool _isAttached;

public:
  void attack(Player& player) override;
  void onDeath() override;
  void update(void) override;

public:
  EnemyCommon(Entity &);
};

#endif /* !ENEMYCOMMON_H_ */
