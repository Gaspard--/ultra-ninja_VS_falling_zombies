#ifndef PLAYER_H_
# define PLAYER_H_

# include "Entity.hpp"
# include "Vect.hpp"

class Player
{
private:
  Entity &_e;

public:
  Player(Entity &e);

  void update(void);
  void setSpeed(Vect<2, double>);
};

#endif /* !PLAYER_H_ */
