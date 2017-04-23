#ifndef ENEMYLARGE_H_
# define ENEMYLARGE_H_

# include "Enemy.hpp"

class EnemyLarge : public Enemy
{
private:

public:
  void attack(Player& player) override;

public:
  EnemyLarge(Entity &);
  void  update(void) override;
};

#endif /* !ENEMYLARGE_H_ */
