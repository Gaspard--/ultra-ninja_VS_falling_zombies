# include "Entity.hpp"

Physics::Fixture&       Entity::getFixture(void)
{
  return (_fixture);
}

const Physics::Fixture& Entity::getFixture(void) const
{
  return (_fixture);
}
