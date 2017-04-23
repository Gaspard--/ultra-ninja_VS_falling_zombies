#ifndef ENEMYLARGE_H_
# define ENEMYLARGE_H_

# include "Enemy.hpp"

class EnemyLarge : public Enemy
{
private:
public:
  EnemyLarge(Entity &);

  // SPIKE
  void attack(Player& player) override;

  void  update(void);
};

#endif /* !ENEMYLARGE_H_ */
