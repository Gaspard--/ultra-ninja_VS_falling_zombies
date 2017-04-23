#ifndef SWORD_HPP_
# define SWORD_HPP_

# include "Entity.hpp"
# include "Vect.hpp"
# include "Enemy.hpp"

struct Sword
{
  Entity &entity;
  Vect<2u, float> knockback;
  int damage;
  bool isUseless = false;

  Sword(Entity &entity, Vect<2u, double> knockback);
  ~Sword();

  void Hit(Enemy &);
};

#endif // !SWORD_HPP_
