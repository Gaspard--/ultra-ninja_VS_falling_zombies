#include "SoundHandler.hpp"

std::unique_ptr<SoundHandler> SoundHandler::_instance(nullptr);

SoundHandler::SoundHandler()
{
}

void SoundHandler::initSoundHandler()
{
  _instance.reset(new SoundHandler());
  if (!_instance->mainMusic.openFromFile("resources/small_world.ogg"))
    throw ("Music not charged");
  // _instance->addSound(BOYAUX, "resources/boyaux.bmp");
  // Already loaded in display.cpp
  // _instance->addSound(PLANET, "resources/planet.bmp");
  // _instance->addSound(SWORDRADIUS, "resources/swordRadius.bmp");
  // _instance->addSound(TEST, "resources/test.bmp");
}

SoundHandler& SoundHandler::getInstance()
{
  return *_instance;
}

void SoundHandler::destroySoundHandler()
{
  _instance.reset(nullptr);
}


void SoundHandler::playMainMusic()
{
  mainMusic.setLoop(true);
  mainMusic.setVolume(40);
  mainMusic.play();
}

void SoundHandler::addSound(SoundList id, std::string const& path)
{
  _instance->_sound[id] = new sf::SoundBuffer();
  _instance->_sound[id]->loadFromFile(path);
}

sf::SoundBuffer* SoundHandler::getSound(SoundList id) const
{
  return (_instance->_sound[id]);
}
