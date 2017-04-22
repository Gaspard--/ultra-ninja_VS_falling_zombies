#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "Physics.hpp"

/*
** kind of entity class
*/

class   Entity
{

public:

  void  collision(const Entity& e) {(void)e; /* some stuff ... */ }

  Physics::Fixture&             getFixture(void);
  const Physics::Fixture&       getFixture(void) const;

  void  setIsOnPlanet(bool);

  void update(void);

private:

  Physics::Fixture      _fixture;
  bool                  _isOnPlanet;

};


#endif /* ENTITY_HPP */
