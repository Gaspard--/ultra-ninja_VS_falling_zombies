#ifndef ENEMYSMALL_H_
# define ENEMYSMALL_H_

# include "Enemy.hpp"

class EnemySmall : public Enemy
{
private:

public:
  void attack(Player& player) override;

public:
  EnemySmall(Entity &);
  void  update(const Player&) override;
};

#endif /* !ENEMYSMALL_H_ */
