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
  void update(const Player& player) override;
};

#endif /* !ENEMYSHOOTER_H_ */
