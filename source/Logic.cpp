//
// Logic.cpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/source/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:30:13 2017 Louis Guittard
// Last update Sat Apr 22 22:08:25 2017 Louis Guittard
//

#include "Logic.hpp"

Logic::Logic()
: _physics(Vect<2, int>(0, 0), 0.4, 1000)
{
}

void Logic::tick(void)
{
  this->_physics.makePhysicsOnEntity(_entities.begin(), _entities.end());
  for_each_entity([](Entity &e) { e.update(); });
}
