#include "Logic.hpp"
#include "Input.hpp"
#include "display.hpp"
#include "EnemyCommon.hpp"

Logic::Logic()
  : _physics(Vect<2, int>(0, 0), 0.4, 1000),
    _entities({std::shared_ptr<Entity>(new Entity({{0, 2}, {0, 0}, 0.04, 100}))}),
    _player(*_entities[0]),
    _mousePos({0, 0})
{
  _entities.push_back(std::shared_ptr<Entity>(new Entity({{1, 0}, {0, 0}, 0.08, 10})));
  _enemies.push_back(std::shared_ptr<Enemy>(new EnemyCommon(*_entities.back())));
}

void Logic::tick(void)
{
  this->_physics.makePhysicsOnEntity(_entities.begin(), _entities.end());
  for_each_entity([](auto &e) { e->update(); });
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

void Logic::checkEvents(Display const &display)
{
  if (display.isKeyPressed(GLFW_KEY_RIGHT))
    this->_player.acceleration(-1);
  if (display.isKeyPressed(GLFW_KEY_LEFT))
    this->_player.acceleration(1);
  if (display.isKeyPressed(GLFW_KEY_SPACE) || display.isKeyPressed(GLFW_KEY_UP))
    this->_player.jump();
  if (display.isKeyPressed(GLFW_KEY_DOWN))
    this->_player.fastFall();
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
