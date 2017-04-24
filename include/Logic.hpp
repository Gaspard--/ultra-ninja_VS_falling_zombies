#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <random>
# include <algorithm>
# include <vector>
# include <memory>
# include "Entity.hpp"
# include "Input.hpp"
# include "Enemy.hpp"
# include "Flesh.hpp"
# include "Player.hpp"
# include "Sword.hpp"

class Display;

class Logic
{
private:

  static std::unique_ptr<Logic> _instance;

  Physics _physics;
  std::vector<std::shared_ptr<Entity>> _entities;
  std::vector<std::shared_ptr<Entity>> _projectiles;
  std::vector<std::shared_ptr<Enemy>> _enemies;
  std::vector<std::shared_ptr<Flesh>> _fleshs;
  std::vector<std::shared_ptr<Sword>> _swords;
  Player _player;
  unsigned int  _time;

  Vect<2u, float> _mousePos;

private:
  Logic();

  void handleKey(GLFWwindow *window, Key key);
  void handleMouse(GLFWwindow *window, Mouse mouse);
  void handleButton(GLFWwindow *window, Button button);

  template <typename T>
  void _addEnemy(Vect<2, double> pos)
  {
    _entities.push_back(std::shared_ptr<Entity>(new Entity({pos, {0, 0}, 0, 0})));
    _enemies.push_back(std::shared_ptr<Enemy>(new T (*_entities.back())));
  }

  void _addSword(Vect<2, double> pos, Vect<2, double> knockback);
  void spawnEnemy();

public:
  static void initLogic();
  static Logic& getInstance();
  static void destroyLogic();

  void handleEvent(Event const& event);
  void checkEvents(Display const &);
  float getPlanetSize(void) const;
  void tick(void);

  template<class Func>
  void addFlesh(Entity const &entityParent, Func func, bool projectile)
  {
    (projectile ? _projectiles : _entities).push_back(std::shared_ptr<Entity>(new Entity(entityParent)));
    Entity &e(*(projectile ? _projectiles : _entities).back());

    func(e);
    _fleshs.push_back(std::shared_ptr<Flesh>(new Flesh(e)));
  }

  Vect<2, double> getPlayerPos(void) const;
  Player& getPlayer();
  Vect<2u, float> getMouse() const;

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

  template <class func>
  void for_each_projectile(func f) const
  {
    std::for_each(_projectiles.begin(), _projectiles.end(), f);
  }

  template <class func>
  void for_each_projectile(func f)
  {
    std::for_each(_projectiles.begin(), _projectiles.end(), f);
  }

  template <class func>
  void for_each_enemy(func f)
  {
    std::for_each(_enemies.begin(), _enemies.end(), f);
  }

  template <class func>
  void for_each_flesh(func f)
  {
    std::for_each(_fleshs.begin(), _fleshs.end(), f);
  }

  template <class func>
  void for_each_swords(func f)
  {
    std::for_each(_swords.begin(), _swords.end(), f);
  }
};

#endif // !LOGIC_HPP_
