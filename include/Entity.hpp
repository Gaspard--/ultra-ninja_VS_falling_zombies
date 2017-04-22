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

private:

  Physics::Fixture      _fixture;

};


#endif /* ENTITY_HPP */