#include "Entity.hpp"

Entity::Entity(Physics::Fixture f, bool b, std::function<void(Entity&)> collision, std::function<void(Entity&)> damage)
  : fixture(f), isOnPlanet(b),
    collision(collision), damage(damage)
{
}

void Entity::update(void)
{
  renderable.destPos = fixture.pos;
}
