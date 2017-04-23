#ifndef PLAYER_H_
# define PLAYER_H_

# include "Entity.hpp"
# include "Vect.hpp"

class Player
{
private:

public:
  Player(Entity &e);

  Entity &entity;

  void update(void);
  void acceleration(int dir);
  void jump();
  void fastFall();
};

#endif /* !PLAYER_H_ */
