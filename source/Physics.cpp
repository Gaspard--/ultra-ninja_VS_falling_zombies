# include "Physics.hpp"
# include "Entity.hpp"

const double    Physics::_G = 6.67384 * pow(10.0, -11.0);

bool    Physics::haveCollision(const Fixture& a, const Fixture& b) const
{
  return (a.pos - b.pos).length2() < CAR(a.radius + b.radius);
}

bool                    Physics::move(Fixture& fixture) const
{
  double                distance;
  Vect<2, double>       vec(0, 0);

  fixture.pos += fixture.speed;
  distance = sqrt((fixture.pos - _planet.pos).length2());
  vec = (fixture.pos - _planet.pos) / distance;
  /* Is fixture touching the planet ?*/
  if (haveCollision(fixture, _planet))
    {
      /* fix the fixture to the planet ground */
      fixture.pos += vec * ((fixture.radius + _planet.radius) - distance);
      /* delete speed against planet */
      fixture.speed -= vec * (vec.scalar(fixture.speed)) * (1.0 + fixture.bounciness);
      /* friction */
      fixture.speed *= 0.95;
    }
  /* application of gravity */
  // fixture.speed -= vec * ((_G * fixture.mass * _planet.mass / CAR(distance)) * fixture.mass);
  fixture.speed -= vec * fixture.mass * 0.00002;
  fixture.speed *= 0.96;
  return (fixture.pos - _planet.pos).length2() < CAR(fixture.radius + _planet.radius) + 0.001;
}

double  Physics::getPlanetRadius(void) const
{
  return (_planet.radius);
}
