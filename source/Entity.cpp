#include "Entity.hpp"

void Entity::update(void)
{
  renderable.destSize = renderable.sourceSize;
  renderable.destPos = fixture.pos;
}
