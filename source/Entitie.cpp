# include "Entitie.hpp"

Physics::Fixture&       Entitie::getFixture(void)
{
  return (_fixture);
}

const Physics::Fixture& Entitie::getFixture(void) const
{
  return (_fixture);
}
