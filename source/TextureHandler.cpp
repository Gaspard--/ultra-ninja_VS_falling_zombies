#include "TextureHandler.hpp"

std::unique_ptr<TextureHandler> TextureHandler::_instance(nullptr);

void TextureHandler::initTextureHandler()
{
  _instance.reset(new TextureHandler());
}

TextureHandler& TextureHandler::getInstance()
{
  return *_instance;
}

void TextureHandler::destroyTextureHandler()
{
  _instance.reset(nullptr);
}
