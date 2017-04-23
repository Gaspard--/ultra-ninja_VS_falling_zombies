#ifndef PLAYER_H_
# define PLAYER_H_

# include "Entity.hpp"

class Player
{
private:
  Entity &_e;

public:
  Player(Entity &e);

  void update(void);
};

#endif /* !PLAYER_H_ */
