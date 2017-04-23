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

  Renderable const &getRenderable() const;

  Physics::Fixture &getFixture(void);

private:

  Physics::Fixture      _fixture;
  bool                  _isOnPlanet;
  Renderable		_renderable;
};

#endif /* ENTITY_HPP */
