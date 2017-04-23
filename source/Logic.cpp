#include "Logic.hpp"
#include "Input.hpp"
#include "display.hpp"
#include "EnemyCommon.hpp"
#include "EnemyLarge.hpp"
#include "EnemySmall.hpp"

Logic::Logic()
  : _physics(Vect<2, int>(0, 0), 0.4, 1000),
    _entities({std::shared_ptr<Entity>(new Entity({{0, 2}, {0, 0}, 0.04, 50}))}),
    _player(*_entities[0]),
    _mousePos({0, 0})
{
  _time = 0;
}

void Logic::tick(void)
{
  _time++;
  if (!(rand() % (unsigned int)(_enemies.size() * 20 + 10 + (50 / (_time / 60.0 + 1)))))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      switch (rand() % 3)
        {
        case 0:
          _addEnemy<EnemySmall>(enemyPos);
          break;
        case 1:
          _addEnemy<EnemyCommon>(enemyPos);
          break;
        case 2:
          _addEnemy<EnemyLarge>(enemyPos);
          break;
        default:
          break;
        }
    }
  this->_physics.makePhysicsOnEntity(_entities.begin(), _entities.end());
  for_each_entity([](auto &e) { e->update(); });
  for_each_enemy([](auto &e) { e->update(); });
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
  if (!_player.canMove)
    return;

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
    // TODO Ajouter la création d'une Sword lors d'un clic + Cooldown sur attaque.
  (void)button;
}

Vect<2, double> Logic::getPlayerPos(void) const
{
  return _player.entity.fixture.pos;
}
