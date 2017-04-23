//
// Logic.cpp for  in /home/sheep/worktree/ultra-ninja_VS_falling_zombies/source/
//
// Made by Louis Guittard
// Login   <guitta_l@epitech.eu>
//
// Started on  Sat Apr 22 10:30:13 2017 Louis Guittard
// Last update Sun Apr 23 05:06:41 2017 Louis Guittard
//

#include "Logic.hpp"
#include "Input.hpp"

Logic::Logic()
  : _physics(Vect<2, int>(0, 0), 0.4, 1000),
    _entities({Entity({{0, 1}, {0, 0}, 0.04, 10})}),
    _player(_entities[0]),
    _mousePos({0, 0})
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
    case GLFW_KEY_LEFT:
      this->_player.acceleration(-1);
      break;
    case GLFW_KEY_RIGHT:
      this->_player.acceleration(1);
      break;
    case GLFW_KEY_UP:
    case GLFW_KEY_SPACE:
      this->_player.jump();
      break;
    case GLFW_KEY_DOWN:
      this->_player.fastFall();
      break;
    }
}

void Logic::handleMouse(GLFWwindow *, Mouse mouse)
{
  int width = 1920;
  int height = 1080;

  _mousePos = {mouse.x, mouse.y};
  _mousePos = (_mousePos - Vect<2u, double>(width - height, 0) * 0.5) / Vect<2u, double>(height * 0.5, -height * 0.5) + Vect<2u, double>(-1.0, 1.0);
}

void Logic::handleButton(GLFWwindow *, Button button)
{
  (void)button;
}
