#ifndef ENTITIES_HPP
# define ENTITIES_HPP

# include "Physics.hpp"

/*
** kind of entities class
*/

class   Entities
{

public:

  void  collision(const Entities& e) {(void)e; /* some stuff ... */ }

  Physics::Fixture&             getFixture(void);
  const Physics::Fixture&       getFixture(void) const;

private:

  Physics::Fixture      _fixture;

};


#endif /* ENTITIES_HPP */
