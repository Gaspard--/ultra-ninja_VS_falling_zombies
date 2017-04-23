#include "Logic.hpp"
#include "Input.hpp"
#include "display.hpp"
#include "EnemyCommon.hpp"
#include "EnemyLarge.hpp"
#include "EnemySmall.hpp"

std::unique_ptr<Logic> Logic::_instance(nullptr);

Logic::Logic()
  : _physics(Vect<2, int>(0, 0), 0.6, 1000),
    _entities({std::shared_ptr<Entity>(new Entity({{0, 2}, {0, 0}, 0.04, 50}))}),
    _player(*_entities[0]),
    _mousePos({0, 0})
{
  _time = 0;
}

void Logic::spawnEnemy()
{
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
        }
    }
}

void Logic::tick(void)
{
  _time++;
  spawnEnemy();
  this->_physics.updateFixtures(_entities.begin(), _entities.end());
  for (auto i(_enemies.begin()); i != _enemies.end(); ++i)
    if (_physics.haveCollision((*i)->entity.fixture, _player.entity.fixture))
      (*i)->attack(_player);
  for (auto i(_enemies.begin()); i != _enemies.end(); ++i)
    for (auto j(_swords.begin()); j != _swords.end(); ++j)
      if (_physics.haveCollision((*i)->entity.fixture, (*j)->entity.fixture))
	(*j)->Hit(**i);
  for_each_entity([](auto &e) { e->update(); });
  for_each_enemy([](auto &e) { e->update(); });
  for_each_flesh([](auto &e) { e->update(); });

  std::remove_if(_enemies.begin(), _enemies.end(), [](auto const &e){ return e->isUseless; });
  std::remove_if(_entities.begin(), _entities.end(), [](auto const &e){ return e->isUseless; });
  std::remove_if(_swords.begin(), _swords.end(), [](auto const &s){ return s->isUseless; });
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
  if (_player.canMove)
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

  if (display.isKeyPressed(GLFW_KEY_C))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      _addEnemy<EnemySmall>(enemyPos);
    }
  if (display.isKeyPressed(GLFW_KEY_V))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      _addEnemy<EnemyCommon>(enemyPos);
    }
  if (display.isKeyPressed(GLFW_KEY_B))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      _addEnemy<EnemyLarge>(enemyPos);
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
  // TODO Ajouter la création d'une Sword lors d'un clic + Cooldown sur attaque.
  Vect<2u, double> vec(_mousePos - _player.getPos());

  _addSword(_player.getPos() + vec * 0.3, vec);
  (void)button;
}

Vect<2, double> Logic::getPlayerPos(void) const
{
  return _player.entity.fixture.pos;
}

void Logic::addFlesh(Entity &entityParent)
{
  _entities.push_back(std::shared_ptr<Entity>(new Entity(entityParent)));
  _fleshs.push_back(std::shared_ptr<Flesh>(new Flesh(*_entities.back())));
}

void Logic::initLogic()
{
  _instance.reset(new Logic());
}

Logic& Logic::getInstance()
{
  return *_instance;
}

void Logic::destroyLogic()
{
  _instance.reset(nullptr);
}

Player& Logic::getPlayer()
{
  return _player;
}

void Logic::_addSword(Vect<2, double> pos, Vect<2, double> knockback)
{
  _entities.push_back(std::shared_ptr<Entity>(new Entity(pos, {0, 0}, 0.06, 0)));
  _swords.push_back(std::shared_ptr<Sword>(new Sword(_entities.back(), knockback)));
}
