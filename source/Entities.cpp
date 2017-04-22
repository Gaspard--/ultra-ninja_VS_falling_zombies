# include "Entities.hpp"

Physics::Fixture&       Entities::getFixture(void)
{
  return (_fixture);
}

const Physics::Fixture& Entities::getFixture(void) const
{
  return (_fixture);
}
