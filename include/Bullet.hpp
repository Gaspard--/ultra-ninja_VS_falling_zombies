#ifndef BULLET_H_
# define BULLET_H_

# include "Enemy.hpp"

struct Bullet
{
  Bullet(Entity &entity);
  ~Bullet();

  Entity &entity;
  int damage;
  int lifetime;
  bool isUseless = false;
  bool _lock = false;

  void update();
  void hit(Player &);
};

#endif /* !BULLET_H_ */
