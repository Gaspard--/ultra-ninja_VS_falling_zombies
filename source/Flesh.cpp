#include "Flesh.hpp"
#include "TextureHandler.hpp"

#include <iostream>

Flesh::Flesh(Entity &e)
  : entity(e)
{
  isUseless = false;
  cooldown = rand() % 120;
  e.isUseless = false;
  e.fixture.bounciness = 1.0;
}

void Flesh::update(void)
{
  entity.fixture.radius *= 0.99;
  entity.renderable.destSize *= 0.99;
  isUseless = (entity.fixture.radius <= 0.01);
  entity.isUseless = isUseless;
  ++cooldown;
}
