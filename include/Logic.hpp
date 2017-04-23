//
// Logic.hpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/include/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:13:21 2017 Louis Guittard
// Last update Sun Apr 23 00:18:56 2017 Louis Guittard
//

#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <algorithm>
# include <vector>
# include "Entity.hpp"
# include "Input.hpp"
# include "Enemy.hpp"
# include "Player.hpp"

class Logic
{
private:
  std::vector<Entity> _entities;
  std::vector<Enemy *> _enemies;
  Player _player;
  Physics _physics;

  Vect<2u, float> _mousePos;

private:
  void handleKey(GLFWwindow *window, Key key);
  void handleMouse(GLFWwindow *window, Mouse mouse);
  void handleButton(GLFWwindow *window, Button button);

public:
  Logic();

  void handleEvent(Event const& event);
  float getPlanetSize(void) const;
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
