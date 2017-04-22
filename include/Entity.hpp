#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <functional>
# include "Physics.hpp"
# include "renderable.hpp"

/*
** kind of entity class
*/
struct Entity
{
  bool isOnPlanet;
  Renderable renderable;
  Physics::Fixture fixture;

  std::function<void(Entity&)> collision;

  void update(void);
};

#endif /* ENTITY_HPP */
