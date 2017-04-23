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
  Entity(Physics::Fixture={{0, 0}, {0, 0}, 0, 0}, bool b=false);

  std::function<void(Entity&)> collision;

  void update(void);

  Physics::Fixture      fixture;
  bool                  isOnPlanet;
  Renderable		renderable;
};

#endif /* ENTITY_HPP */
