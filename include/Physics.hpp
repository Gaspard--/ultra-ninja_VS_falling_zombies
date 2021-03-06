#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "Vect.hpp"
# include <cmath>
# include <vector>

struct Entity;

# define CAR(x) ((x) * (x))

class   Physics
{

public:

  /************************************/
  /*                                  */
  /*    Fixture struct declaration    */
  /*                                  */
  /************************************/

  Physics(const Vect<2, int>& planetCenter, double radius, double mass)
    : _planet{planetCenter, Vect<2, int>(0, 0), radius, mass, 0.0} {}

  struct                Fixture
  {
    Vect<2, double>     pos;
    Vect<2, double>     speed;
    double              radius;
    double              mass;
    double		bounciness{0.0};
  };

  /****************************/
  /*                          */
  /*    Fixture management    */
  /*                          */
  /****************************/

  bool  haveCollision(const Fixture&, const Fixture&) const;
  bool  move(Fixture&) const;

  /****************************/
  /*                          */
  /*  Entity management ...   */
  /*                          */
  /****************************/

  template <class T>
  void updateFixtures(T begin, T end)
  {
    for (T i = begin ; i != end ; ++i)
      (*i)->isOnPlanet = this->move((*i)->fixture);
  }

  /* Planet size getter */

  double        getPlanetRadius(void) const;

private:

  const Fixture _planet;

  static const double   _G;

};


#endif /* PHYSICS_HPP */
