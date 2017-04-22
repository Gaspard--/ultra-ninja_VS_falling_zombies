#ifndef ENTITIE_HPP
# define ENTITIE_HPP

# include "Physics.hpp"

/*
** kind of entitie class
*/

class   Entitie
{

public:

  void  collision(const Entitie& e) {(void)e; /* some stuff ... */ }

  Physics::Fixture&             getFixture(void);
  const Physics::Fixture&       getFixture(void) const;

private:

  Physics::Fixture      _fixture;

};


#endif /* ENTITIE_HPP */
