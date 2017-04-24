#include "Flesh.hpp"
#include "TextureHandler.hpp"

#include <iostream>

Flesh::Flesh(Entity &e)
  : entity(e)
{
  isUseless = false;
  cooldown = 0;
  e.isUseless = false;
}

void Flesh::update(void)
{
  isUseless = (cooldown >= 240);
  entity.isUseless = isUseless;
  ++cooldown;
}
