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
  /* Is fixture touching the planet ?*/
  if (haveCollision(fixture, _planet))
    {
      /* fix the fixture to the planet ground */
      fixture.pos += vec * ((fixture.radius + _planet.radius) - distance);
      /* delete speed against planet */
      fixture.speed -= vec * (vec.x() * fixture.speed.x() + vec.y() * fixture.speed.y());
      /* friction */
      fixture.speed *= 0.9;
      return (true);
    }
  /* application of gravity */
  fixture.speed *= vec * ((_G * fixture.mass * _planet.mass / CAR(distance)) * fixture.mass);
  /* friction */
  fixture.speed *= 0.99;
  return (false);
}

double  Physics::getPlanetRadius(void) const
{
  return (_planet.radius);
}
