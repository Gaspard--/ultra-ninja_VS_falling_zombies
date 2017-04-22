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
#include "Input.hpp"

Logic::Logic()
{
}

void Logic::tick(void)
{
  std::for_each(_entities.begin(), _entities.end(),
		[](Entity &e) { e.update(); });
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
