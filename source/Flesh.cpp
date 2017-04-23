#include "Flesh.hpp"

#include <iostream>

Flesh::Flesh(Entity &e)
  : entity(e)
{
  isUseless = false;
  cooldown = 0;
  e.fixture.radius = 0.01;
  // e.renderable.sourceSize = {1, 1};
  // e.renderable.sourcePos = {0, 0};
  e.renderable.texture = my_opengl::loadTexture("resources/test.bmp");
  std::cout << "sourceSize[0] --> " << e.renderable.sourceSize[0] << std::endl;
}

void Flesh::update(void)
{
  if (cooldown == 240)
    isUseless = true;
  cooldown++;
}
