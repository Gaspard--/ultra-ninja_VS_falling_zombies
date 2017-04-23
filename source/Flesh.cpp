#include "Flesh.hpp"

Flesh::Flesh(Entity &e)
  : entity(e)
{
  isUseless = false;
  cooldown = 0;
  e.fixture.radius = 0.01;
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
}

void Flesh::update(void)
{
  if (cooldown == 240)
    isUseless = true;
  cooldown++;
}
