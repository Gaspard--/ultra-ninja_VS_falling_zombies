#ifndef PHYSICS_HPP
# define PHYSICS_HPP

# include "vect.hpp"
# include <cmath>
# include <vector>

class Entities;

# define CAR(x) ((x) * (x))

class   Physics
{

public:

  /************************************/
  /*                                  */
  /*    Fixture struct declaration    */
  /*                                  */
  /************************************/

  struct                Fixture
  {
    Fixture(const Vect<2, int>& i_pos, const Vect<2, int>& i_speed, double i_radius) : pos(i_pos), speed(i_speed), radius(i_radius) {}

    Vect<2, int>        pos;
    Vect<2, int>        speed;
    double              radius;
  };

  /****************************/
  /*                          */
  /*    Fixture management    */
  /*                          */
  /****************************/

  bool  haveCollision(const Fixture&, const Fixture&) const;
  void  move(Fixture&) const;

  /****************************/
  /*                          */
  /*  Entities management ... */
  /*                          */
  /****************************/

  void  makePhysicesOnEntities(const std::vector<Entities *>&) const;

private:


};


#endif /* PHYSICS_HPP */