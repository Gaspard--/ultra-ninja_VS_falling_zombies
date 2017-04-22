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

  Physics(const Vect<2, int>& planetCenter, double radius, double mass) : _planet(planetCenter, Vect<2, int>(0, 0), radius, mass) {}

  struct                Fixture
  {
    Fixture(const Vect<2, int>& i_pos, const Vect<2, int>& i_speed, double i_radius, double i_mass) : pos(i_pos),
                                                                                                      speed(i_speed),
                                                                                                      radius(i_radius),
                                                                                                      mass(i_mass){}

    Vect<2, int>        pos;
    Vect<2, int>        speed;
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

  void  makePhysicsOnEntity(const std::vector<Entity *>&) const;

private:

  const Fixture _planet;

  static const double   _G;

};


#endif /* PHYSICS_HPP */
