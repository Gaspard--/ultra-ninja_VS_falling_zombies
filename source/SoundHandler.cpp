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
  _instance->addSoundBuffer(SHOOT, "resources/shoot.wav");
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
  mainMusic.setVolume(30);
  mainMusic.play();
}

void SoundHandler::playSound(SoundList id, int volume)
{
  sf::Sound* sound = new sf::Sound();
  sound->setBuffer(*_instance->getSoundBuffer(id));
  sound->setLoop(false);
  sound->setVolume(volume);
  sound->play();
  _instance->_soundsPlaying.push_back(sound);
}

void SoundHandler::deleteSounds()
{
  std::vector<sf::Sound *>::iterator it(_instance->_soundsPlaying.begin());
  while (it != _instance->_soundsPlaying.end())
    {
      if ((*it)->getStatus() != sf::SoundSource::Status::Playing)
	{
	  delete *it;
          it = _instance->_soundsPlaying.erase(it);
	}
      else
        ++it;
    }
}

void SoundHandler::addSoundBuffer(SoundList id, std::string const& path)
{
  _instance->_sound[id] = new sf::SoundBuffer();
  _instance->_sound[id]->loadFromFile(path);
}

sf::SoundBuffer* SoundHandler::getSoundBuffer(SoundList id) const
{
  return (_instance->_sound[id]);
}
