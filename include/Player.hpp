#ifndef PLAYER_H_
# define PLAYER_H_

# include "Entity.hpp"
# include "Vect.hpp"

class Player
{
private:

public:
  Player(Entity &e, bool canMove = true);

  Entity &entity;
  bool canMove;

  void update(void);
  void acceleration(int dir);
  void jump();
  void fastFall();
};

#endif /* !PLAYER_H_ */
