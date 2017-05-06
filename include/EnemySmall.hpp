#ifndef ENEMYSMALL_H_
# define ENEMYSMALL_H_

# include <cstdlib>
# include "Enemy.hpp"

class EnemySmall : public Enemy
{
private:

  int   _dir;
  const double  _attackDist;
  bool          _dash;

public:
  void attack(Player& player) override;

public:
  EnemySmall(Entity &);
  bool  update(const Player&) override;
};

#endif /* !ENEMYSMALL_H_ */
