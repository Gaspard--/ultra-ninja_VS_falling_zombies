#ifndef SWORD_HPP_
# define SWORD_HPP_

# include "Entity.hpp"
# include "Vect.hpp"
# include "Enemy.hpp"

struct Sword
{
  Entity &entity;
  int damage;
  int lifetime;
  Vect<2u, float> knockback;
  bool isUseless = false;

  Sword(Entity &entity, Vect<2u, double> knockback);
  ~Sword();

  void update();
  void hit(Enemy &, Player &);
};

#endif // !SWORD_HPP_
