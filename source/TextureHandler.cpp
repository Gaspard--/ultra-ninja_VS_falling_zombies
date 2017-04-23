#include "TextureHandler.hpp"

std::unique_ptr<TextureHandler> TextureHandler::_instance(nullptr);

void TextureHandler::initTextureHandler()
{
  _instance.reset(new TextureHandler());
  _instance->addTexture(BOYAUX, "resources/boyaux.bmp");
  _instance->addTexture(BOYAUX, "resources/planet.bmp");
  _instance->addTexture(BOYAUX, "resources/swordRadius.bmp");
  _instance->addTexture(BOYAUX, "resources/test.bmp");
}

TextureHandler& TextureHandler::getInstance()
{
  return *_instance;
}

void TextureHandler::destroyTextureHandler()
{
  _instance.reset(nullptr);
}

void TextureHandler::addTexture(TextureList id, std::string path)
{
  _instance->_textures[id] = my_opengl::loadTexture(path);
}

Texture TextureHandler::getTexture(TextureList id) const
{
  return (_instance->_textures[id]);
}
