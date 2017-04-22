# include "Physics.hpp"
# include "Entity.hpp"

const double    Physics::_G = 6.67384 * pow(10.0, -11.0);

bool    Physics::haveCollision(const Fixture& a, const Fixture& b) const
{
  return (sqrt(CAR(a.pos.x() - b.pos.x()) + CAR(a.pos.y() - b.pos.y())) < a.radius + b.radius);
}

bool                    Physics::move(Fixture& fixture) const
{
  double                distance;
  Vect<2, double>       vec(0, 0);

  fixture.pos += fixture.speed;
  distance = sqrt(CAR(fixture.pos.x() - _planet.pos.x()) + CAR(fixture.pos.y() - _planet.pos.y()));
  vec = Vect<2, double>((fixture.pos.x() - _planet.pos.x()) / distance, (fixture.pos.y() - _planet.pos.y()) / distance);
  if (haveCollision(fixture, _planet))
    {
      vec *= (fixture.radius + _planet.radius) - distance;
      fixture.pos += vec;
      return (true);
    }
  fixture.speed *= vec * ((_G * fixture.mass * _planet.mass / CAR(distance)) * fixture.mass);
  return (false);
}

void    Physics::makePhysicsOnEntity(const std::vector<Entity *>& ent) const
{
  for (unsigned int i = 0 ; i < ent.size() ; i++)
    if (this->move(ent[i]->getFixture()))
      ent[i]->setIsOnPlanet(true);

  for (unsigned int i = 0 ; i < ent.size() ; i++)
    for (unsigned int j = i + 1 ; j < ent.size() ; j++)
      if (haveCollision(ent[i]->getFixture(), ent[j]->getFixture()))
        {
          ent[i]->collision(*ent[j]);
          ent[j]->collision(*ent[i]);
        }
}
