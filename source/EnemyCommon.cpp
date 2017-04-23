#include "EnemyCommon.hpp"

EnemyCommon::EnemyCommon(Entity &e)
  : Enemy(e, 20)
{
  e.fixture.radius = 0.05;
  e.fixture.mass = 15;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void    EnemyCommon::update(void)
{
  if (this->_e.isOnPlanet && !(rand() % 5))
    this->_e.fixture.speed = this->_e.fixture.speed + this->_e.fixture.pos.normalized() * 0.03;
}
