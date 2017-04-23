#ifndef ENEMYSHOOTER_H_
# define ENEMYSHOOTER_H_

# include "Enemy.hpp"

class EnemyShooter : public Enemy
{
private:
public:
  EnemyShooter(Entity &);

  void attack(Player& player) override;
  void shoot();
};

#endif /* !ENEMYSHOOTER_H_ */
