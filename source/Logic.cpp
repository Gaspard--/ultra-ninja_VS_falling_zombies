#include "Logic.hpp"
#include "Input.hpp"
#include "display.hpp"
#include "SoundHandler.hpp"
#include "EnemyCommon.hpp"
#include "EnemyLarge.hpp"
#include "EnemySmall.hpp"
#include "EnemyShooter.hpp"

std::unique_ptr<Logic> Logic::_instance(nullptr);

Logic::Logic(unsigned int maxMobs)
  : _physics(Vect<2, int>(0, 0), 0.6, 1000),
    _entities({std::shared_ptr<Entity>(new Entity({{0, 2}, {0, 0}, 0.04, 50}))}),
    _player(*_entities[0]),
    _maxMobs(maxMobs),
    _mousePos({0, 0})
{
  _time = 0;
  _score = 0;
  _gameOver = false;
  _combo = 0;
  _multiplier = 0;
}

void Logic::spawnEnemy()
{
  if (!(rand() % (unsigned int)(_enemies.size() * 20 + 10 + (50 / (_time / 60.0 + 1)))))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      switch (rand() % 4)
        {
        case 0:
          if (_time / 60 > 30)
            _addEnemy<EnemyLarge>(enemyPos);
          else
            _addEnemy<EnemySmall>(enemyPos);
          break;
        case 1:
          if (_time / 60 > 15)
            _addEnemy<EnemyCommon>(enemyPos);
          else
            _addEnemy<EnemySmall>(enemyPos);
          break;
        case 2:
          _addEnemy<EnemySmall>(enemyPos);
          break;
        case 3:
          _addEnemy<EnemyShooter>(enemyPos);
          break;
        }
    }
}

void Logic::tick(void)
{
  _time++;

  spawnEnemy();

  _multiplier += (1.0 / 600.0);

  this->_physics.updateFixtures(_entities.begin(), _entities.end());
  this->_physics.updateFixtures(_projectiles.begin(), _projectiles.end());

  for (auto i(_enemies.begin()); i != _enemies.end(); ++i)
    if (_physics.haveCollision((*i)->entity.fixture, _player.entity.fixture))
      (*i)->attack(_player);

  for (auto i(_enemies.begin()); i != _enemies.end(); ++i)
    for (auto j(_swords.begin()); j != _swords.end(); ++j)
      if (_physics.haveCollision((*i)->entity.fixture, (*j)->entity.fixture))
        (*j)->hit(**i, _player);

  for (auto& s : _shooters)
    if (s->isInRange(_player))
      s->shoot();

  for (auto& b : _bullets)
    if (_physics.haveCollision(_player.entity.fixture, b->entity.fixture))
      b->hit(_player);

  for_each_entity([](auto &e) { e->update(); });
  for_each_projectile([](auto &e) { e->update(); });
  for_each_enemy([this](auto &e) { e->update(_player); });
  for_each_flesh([](auto &f) { f->update(); });
  for_each_swords([](auto &s) { s->update(); });
  for_each_bullet([](auto &b) { b->update(); });
  _player.update();

  _enemies.erase(std::remove_if(_enemies.begin(), _enemies.end(), [](auto const &e){ return e->isUseless; }), _enemies.end());
  _fleshs.erase(std::remove_if(_fleshs.begin(), _fleshs.end(), [](auto const &f){ return f->isUseless; }), _fleshs.end());
  _swords.erase(std::remove_if(_swords.begin(), _swords.end(), [](auto const &s){ return s->isUseless; }), _swords.end());
  _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [](auto const &b){ return b->isUseless; }), _bullets.end());
  _entities.erase(std::remove_if(_entities.begin(), _entities.end(), [](auto const &e){ return e->isUseless; }), _entities.end());
  _projectiles.erase(std::remove_if(_projectiles.begin(), _projectiles.end(), [](auto const &e){ return e->isUseless; }), _projectiles.end());
  SoundHandler::getInstance().deleteSounds();
  if (!this->getRemainingsSpace() && !_gameOver)
    {
      _gameOver = true;
      std::cout << "GAME OVER" << std::endl;
    }
}

void	Logic::addToScore(int add)
{
    _score += _combo * add * (_multiplier == 0 ? 1 : _multiplier);
}

void	Logic::incCombo()
{
    _combo++;
}

void	Logic::resetCombo()
{
    _combo = 0;
}

unsigned int  Logic::getMaxMobs(void) const
{
  return (_maxMobs);
}

unsigned int    Logic::getRemainingsSpace(void) const
{
  unsigned int  remaining;

  remaining = _maxMobs;
  for_each_enemy([&remaining](const auto &e) {if (e->entity.isOnPlanet && remaining) remaining--;});
  if (_player.entity.isOnPlanet && remaining)
    remaining--;
  return (remaining);
}

unsigned int  Logic::getScore(void) const
{
  return (_score);
}

std::string     Logic::getTime(void) const
{
  std::string   toReturn;

  if (_time / 3600 >= 10)
    toReturn = std::to_string(_time / 3600) + " m ";
  else if (_time / 3600)
    toReturn = "0" + std::to_string(_time / 3600) + " m ";
  if ((_time / 60) % 60 >= 10)
    toReturn += std::to_string((_time / 60) % 60) + " s";
  else
    toReturn += "0" + std::to_string((_time / 60) % 60) + " s";
  return (toReturn);
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
      if (display.isKeyPressed(GLFW_KEY_Q))
          this->_player.dash(1);
      if (display.isKeyPressed(GLFW_KEY_E))
          this->_player.dash(-1);
      if (display.isKeyPressed(GLFW_KEY_D) || display.isKeyPressed(GLFW_KEY_RIGHT))
        this->_player.acceleration(-1);
      if (display.isKeyPressed(GLFW_KEY_A) || display.isKeyPressed(GLFW_KEY_LEFT))
        this->_player.acceleration(1);
      if (display.isKeyPressed(GLFW_KEY_SPACE) || display.isKeyPressed(GLFW_KEY_W)
          || display.isKeyPressed(GLFW_KEY_UP))
        this->_player.jump();
      if (display.isKeyPressed(GLFW_KEY_S) || display.isKeyPressed(GLFW_KEY_DOWN))
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
  if (display.isKeyPressed(GLFW_KEY_N))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      _addEnemy<EnemyShooter>(enemyPos);
    }
 if (display.isKeyPressed(GLFW_KEY_J))
    {
      double                angle = std::rand();
      double                dist = (1 + (double)(std::rand() % 10 + 1) / 20.0);
      Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

      addBullet(enemyPos);
    }
}

static inline Vect<2u, float> rotate(Vect<2u, float> a, Vect<2u, float> b)
{
  return {a[0] * b[0] - a[1] * b[1], a[0] * b[1] + a[1] * b[0]};
}

void Logic::handleMouse(GLFWwindow *, Mouse mouse)
{
  Vect<2u, float> const size(Display::getInstance().getSize());

  _mousePos = {mouse.x, mouse.y};
  _mousePos = (_mousePos - Vect<2u, double>(size[0] - size[1], 0) * 0.5) / Vect<2u, double>(size[1] * 0.5, -size[1] * 0.5) + Vect<2u, double>(-1.0, 1.0);
}

Vect<2u, float> Logic::getMouse() const
{
  Vect<2u, float> const camera(Display::getInstance().getCamera());

  return rotate(_mousePos, camera * Vect<2u, float>{1.0f, -1.0f} / camera.length2());
}

void Logic::handleButton(GLFWwindow *, Button button)
{
  Vect<2u, double> vec(getMouse() - getPlayerPos());

  if (button.button != GLFW_MOUSE_BUTTON_LEFT || button.action != GLFW_PRESS)
    return ;
  _addSword(getPlayerPos() + vec.normalized() * 0.04, vec.normalized() * 0.1);
}

Vect<2, double> Logic::getPlayerPos(void) const
{
  return _player.entity.fixture.pos;
}

void Logic::initLogic(unsigned int maxMobs)
{
  _instance.reset(new Logic(maxMobs));
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
  _projectiles.push_back(std::shared_ptr<Entity>(new Entity({pos, knockback * 0.2, 0.06, 0})));
  _swords.push_back(std::shared_ptr<Sword>(new Sword(*_projectiles.back(), knockback)));
}

void Logic::addBullet(Vect<2, double> pos)
{
  _projectiles.push_back(std::shared_ptr<Entity>(new Entity({pos, {0, 0}, 0.06, 0})));
  _bullets.push_back(std::shared_ptr<Bullet>(new Bullet(*_projectiles.back())));
}

template <>
void Logic::_addEnemy<EnemyShooter>(Vect<2, double> pos)
{
  _entities.push_back(std::shared_ptr<Entity>(new Entity({pos, {0, 0}, 0, 0})));
  _enemies.push_back(std::shared_ptr<Enemy>(new EnemyShooter (*_entities.back())));
  _shooters.push_back(std::shared_ptr<EnemyShooter>(std::static_pointer_cast<EnemyShooter>(_enemies.back())));
}
