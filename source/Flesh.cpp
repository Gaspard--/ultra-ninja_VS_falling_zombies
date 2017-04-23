#include "Flesh.hpp"

Flesh::Flesh(Entity &e)
  : entity(e)
{
  e.fixture.radius = 0.01;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
}
