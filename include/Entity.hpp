#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "Physics.hpp"
# include "renderable.hpp"

/*
** kind of entity class
*/

class   Entity
{

public:

  inline void  collision(const Entity& e) {(void)e; /* some stuff ... */ }

  Physics::Fixture&             getFixture(void);
  const Physics::Fixture&       getFixture(void) const;

  void  setIsOnPlanet(bool);

  void update(void);

  Renderable const &getRenderable() const;

private:

  Physics::Fixture      _fixture;
  bool                  _isOnPlanet;
  Renderable		_renderable;
};


#endif /* ENTITY_HPP */
