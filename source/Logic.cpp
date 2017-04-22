//
// Logic.cpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/source/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:30:13 2017 Louis Guittard
// Last update Sun Apr 23 00:34:28 2017 Louis Guittard
//

#include "Logic.hpp"
#include "Input.hpp"

Logic::Logic()
: _physics(Vect<2, int>(0, 0), 0.4, 1000)
{
}

void Logic::tick(void)
{
  this->_physics.makePhysicsOnEntity(_entities.begin(), _entities.end());
  for_each_entity([](Entity &e) { e.update(); });
}

float Logic::getPlanetSize(void) const
{
  return (this->_physics.getPlanetRadius() * 2);
}

void Logic::handleEvent(Event const& event)
{
  if (event)
    {
      switch (event.type)
	{
	case Event::KEY:
	  handleKey(event.window, event.val.key);
	  break;
	case Event::MOUSE:
	  handleMouse(event.window, event.val.mouse);
	  break;
	case Event::BUTTON:
	  handleButton(event.window, event.val.button);
	  break;
	}
    }
}

void Logic::handleKey(GLFWwindow *window, Key key)
{
  switch (key.key)
    {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, true);
      break;
    }
}

void Logic::handleMouse(GLFWwindow *window, Mouse mouse)
{
  (void)window;
  (void)mouse;
}

void Logic::handleButton(GLFWwindow *window, Button button)
{
  (void)window;
  (void)button;
}
