//
// Logic.hpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/include/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:13:21 2017 Louis Guittard
// Last update Sat Apr 22 20:30:35 2017 Louis Guittard
//

#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <algorithm>
# include <vector>
# include "Entity.hpp"

//FIXME: forward declaration of entity ?
class Logic
{
private:
  std::vector<Entity> _entities;
  Physics               _physics;

public:
  Logic();

  void tick(void);

  template <class func>
  void for_each_entity(func f) const
    {
      std::for_each(_entities.begin(), _entities.end(), f);
    }

  template <class func>
  void for_each_entity(func f)
    {
      std::for_each(_entities.begin(), _entities.end(), f);
    }
};

#endif // !LOGIC_HPP_
