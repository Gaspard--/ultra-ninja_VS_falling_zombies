//
// Logic.cpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/source/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:30:13 2017 Louis Guittard
// Last update Sat Apr 22 10:32:09 2017 Louis Guittard
//

#include <algorithm>
#include "Logic.hpp"

Logic::Logic()
{
}

void Logic::tick(void)
{
  std::for_each(_entities.begin(), _entities.end(),
		[](Entity &e) { e.update(); });
}
