#include "Entity.hpp"

void Entity::update(void)
{
  renderable.destPos = fixture.pos;
}

Physics::Fixture &Entity::getFixture(void)
{
  return _fixture;
}
