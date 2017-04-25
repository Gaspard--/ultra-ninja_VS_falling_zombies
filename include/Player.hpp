#ifndef PLAYER_H_
# define PLAYER_H_

# include "Entity.hpp"
# include "Vect.hpp"

class Player
{
private:
  int _hp;
  int _cooldownDash;
  int _animation;
  int _maxAnimationFrame;

public:
  Player(Entity &e, bool canMove = true);

  Entity &entity;
  bool canMove;

  void update(void);
  void acceleration(int dir);
  void dash(int dir);
  void jump();
  void fastFall();
  void getRekt(int);
  void animate();

  static void playRandomPlayerActionSound(void);
  static void playRandomPlayerEuuuhSound(void);
};

#endif /* !PLAYER_H_ */
