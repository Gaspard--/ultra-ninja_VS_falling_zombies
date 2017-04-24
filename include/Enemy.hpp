#ifndef ENEMY_H_
# define ENEMY_H_

# include "Entity.hpp"
# include "Player.hpp"

class Enemy
{
protected:
  int _hp;
  int _coolDown;
  int _animation;

public:
  bool isUseless = false;

  virtual void attack(Player& player) = 0;

public:
  Enemy(Entity &, int hp);
  virtual ~Enemy() = default;

  void animate();
  virtual bool update(const Player&);
  virtual void onDeath();
  void getRekt(int);

  Entity &entity;
};

#endif /* !ENEMY_H_ */
