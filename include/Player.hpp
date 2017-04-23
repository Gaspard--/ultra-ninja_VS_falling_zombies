#ifndef PLAYER_H_
# define PLAYER_H_

# include "Entity.hpp"
# include "Vect.hpp"

class Player
{
private:
  int _hp;

public:
  Player(Entity &e);

  Entity &entity;

  void update(void);
  void acceleration(int dir);
  void jump();
  void fastFall();
  void getRekt(int);
};

#endif /* !PLAYER_H_ */
