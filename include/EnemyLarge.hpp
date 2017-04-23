#ifndef ENEMYLARGE_H_
# define ENEMYLARGE_H_

# include "Enemy.hpp"

class EnemyLarge : public Enemy
{
private:

public:
  // SPIKE
  void attack(Player& player) override;

public:
  EnemyLarge(Entity &);
};

#endif /* !ENEMYLARGE_H_ */
