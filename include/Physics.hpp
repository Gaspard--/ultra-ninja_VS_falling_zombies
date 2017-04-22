#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "vect.hpp"
# include <cmath>
# include <vector>

class Entity;

# define CAR(x) ((x) * (x))

class   Physics
{

public:

  /************************************/
  /*                                  */
  /*    Fixture struct declaration    */
  /*                                  */
  /************************************/

  Physics(const Vect<2, double>& planetCenter, double radius, double mass) : _planet(planetCenter, Vect<2, double>(0, 0), radius, mass) {}

  struct                Fixture
  {
    Fixture(const Vect<2, double>& i_pos, const Vect<2, double>& i_speed, double i_radius, double i_mass) : pos(i_pos),
                                                                                                      speed(i_speed),
                                                                                                      radius(i_radius),
                                                                                                      mass(i_mass){}

    Vect<2, double>     pos;
    Vect<2, double>     speed;
    double              radius;
    double              mass;
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
  void  makePhysicsOnEntity(T begin, T end) const
  {
    for (T i = begin ; i != end ; ++i)
      if (this->move(i->getFixture()))
        i->setIsOnPlanet(true);

    for (T i = begin ; i != end ; ++i)
      for (T j = i + 1 ; j != end ; ++j)
        if (haveCollision(i->getFixture(), j->getFixture()))
          {
            i->collision(*j);
            j->collision(*i);
          }
  }

private:

  const Fixture _planet;

  static const double   _G;

};


#endif /* PHYSICS_HPP */
