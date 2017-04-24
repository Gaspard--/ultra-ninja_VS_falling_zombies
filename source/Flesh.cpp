#include "Flesh.hpp"
#include "TextureHandler.hpp"

#include <iostream>

Flesh::Flesh(Entity &e)
  : entity(e)
{
  isUseless = false;
  cooldown = 0;
  e.fixture.radius = 0.1;
  // e.renderable.sourceSize = {1, 1};
  // e.renderable.sourcePos = {0, 0};
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::TEST);
}

void Flesh::update(void)
{
  if (cooldown == 240)
    isUseless = true;
  cooldown++;
}
