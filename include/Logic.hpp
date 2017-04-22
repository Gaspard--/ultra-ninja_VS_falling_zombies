//
// Logic.hpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/include/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:13:21 2017 Louis Guittard
// Last update Sat Apr 22 10:19:37 2017 Louis Guittard
//

#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>
# include "Entity.hpp"
# include "Input.hpp"

class Logic
{
private:
  std::vector<Entity> _entities;

private:
  void handleKey(GLFWwindow *window, Key key);
  void handleMouse(GLFWwindow *window, Mouse mouse);
  void handleButton(GLFWwindow *window, Button button);

public:
  Logic();

  void handleEvent(Event const& event);
  void tick(void);
};

#endif // !LOGIC_HPP_
