#ifndef ENEMYCOMMON_H_
# define ENEMYCOMMON_H_

# include "Enemy.hpp"

class EnemyCommon : public Enemy
{
private:

public:
  void attack(Player& player) override;
  bool update(const Player&) override;

public:
  EnemyCommon(Entity &);
};

#endif /* !ENEMYCOMMON_H_ */
