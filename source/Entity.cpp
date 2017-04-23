#include "Entity.hpp"

Entity::Entity(Physics::Fixture f, bool b)
  : fixture(f), isOnPlanet(b)
{
}

void Entity::update(void)
{
  renderable.destPos = fixture.pos;
}
