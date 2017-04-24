#ifndef ENEMYSHOOTER_H_
# define ENEMYSHOOTER_H_

# include "Enemy.hpp"

class EnemyShooter : public Enemy
{
private:
public:
  EnemyShooter(Entity &);

  bool isInRange(Player const& player);
  void attack(Player& player) override;
  void shoot(Player const& player);
  bool update(Player const& player) override;
};

#endif /* !ENEMYSHOOTER_H_ */
