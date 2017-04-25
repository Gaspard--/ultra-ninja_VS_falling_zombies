#ifndef ENEMY_H_
# define ENEMY_H_

# include "Entity.hpp"
# include "Player.hpp"

class Enemy
{
protected:
  int _coolDown;
  int _animation;
  int _maxAnimationFrame;

public:
  int _hp;
  bool isUseless = false;

  virtual void attack(Player& player) = 0;

public:
  Enemy(Entity &, int hp);
  virtual ~Enemy() = default;

  void animate();
  virtual bool update(const Player&);
  virtual void onDeath();
  void getRekt(int);

  static void playRandomSpawnSound(void);
  static void playRandomDeathSound(void);

  Entity &entity;
};

#endif /* !ENEMY_H_ */
