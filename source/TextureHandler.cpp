#include "TextureHandler.hpp"

std::unique_ptr<TextureHandler> TextureHandler::_instance(nullptr);

void TextureHandler::initTextureHandler()
{
  _instance.reset(new TextureHandler());
  _instance->_textures[BOYAUX] = my_opengl::loadTexture("resources/test.bmp");
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
  // TextureHandler::getInstance()._textures.insert
}
