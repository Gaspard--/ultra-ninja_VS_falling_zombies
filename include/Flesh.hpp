#ifndef FLESH_HPP_
# define FLESH_HPP_

#include "Entity.hpp"

class Flesh
{
public:
  Flesh(Entity &e);
  void update(void);

  Entity &entity;
  bool isUseless;
};

#endif /* !FLESH_HPP_ */
