#ifndef BULLET_H_
# define BULLET_H_

# include "Enemy.hpp"

struct Bullet
{
  Bullet(Entity &entity, Vect<2u, double> knockback);
  ~Bullet();

  Entity &entity;
  int damage;
  Vect<2u, float> knockback;
  bool isUseless = false;

  void Hit(Enemy &);
};

#endif /* !BULLET_H_ */
