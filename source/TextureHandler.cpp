#include "TextureHandler.hpp"

std::unique_ptr<TextureHandler> TextureHandler::_instance(nullptr);

TextureHandler::TextureHandler()
{
}

void TextureHandler::initTextureHandler()
{
  _instance.reset(new TextureHandler());
  _instance->addTexture(BOYAUX, "resources/boyaux.bmp");
  // Already loaded in display.cpp
  // _instance->addTexture(PLANET, "resources/planet.bmp");
  _instance->addTexture(SWORDRADIUS, "resources/swordRadius.bmp");
  _instance->addTexture(BULLET, "resources/bite.bmp");
  _instance->addTexture(ZOMBIE, "resources/ZombieSpriteSheet.bmp");
  _instance->addTexture(PLAYER, "resources/PlayerSpriteSheet.bmp");
  _instance->addTexture(TEST, "resources/test.bmp");
}

TextureHandler& TextureHandler::getInstance()
{
  return *_instance;
}

void TextureHandler::destroyTextureHandler()
{
  _instance.reset(nullptr);
}

void TextureHandler::addTexture(TextureList id, std::string const& path)
{
  _instance->_textures[id] = my_opengl::loadTexture(path);
}

Texture TextureHandler::getTexture(TextureList id) const
{
  return (_instance->_textures[id]);
}
