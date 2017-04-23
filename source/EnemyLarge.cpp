#include <iostream>
#include "EnemyLarge.hpp"
#include "Player.hpp"

EnemyLarge::EnemyLarge(Entity &e)
  : Enemy(e, 30)
{
  e.fixture.radius = 0.1;
  e.fixture.mass = 10;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemyLarge::attack(Player& player)
{
  std::cout << "oui" << std::endl;
  player.entity.fixture.speed = player.entity.fixture.speed * 0.5
    - player.entity.fixture.pos.normalized() * 0.09 * 0.2;
  entity.fixture.speed = entity.fixture.speed * 0.5
    + entity.fixture.pos.normalized() * 0.09 * 0.2;
  player.getRekt(2);
}

void    EnemyLarge::update(void)
{
}
