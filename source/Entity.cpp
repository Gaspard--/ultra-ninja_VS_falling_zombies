# include "Entity.hpp"

Physics::Fixture&       Entity::getFixture(void)
{
  return (_fixture);
}

const Physics::Fixture& Entity::getFixture(void) const
{
  return (_fixture);
}

void    Entity::setIsOnPlanet(bool isOnPlanet)
{
  _isOnPlanet = isOnPlanet;
}

void Entity::update(void)
{

}

Renderable const &Entity::getRenderable() const
{
  return (_renderable);
}
