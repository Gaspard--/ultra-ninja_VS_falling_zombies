#include <iostream>
#include <algorithm>
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
  _instance->addSoundBuffer(BOYAUX1, "resources/boyaux1.wav");
  _instance->addSoundBuffer(BOYAUX2, "resources/boyaux2.wav");
  _instance->addSoundBuffer(BOYAUX3, "resources/boyaux3.wav");
  _instance->addSoundBuffer(BOYAUX4, "resources/boyaux4.wav");
  _instance->addSoundBuffer(BOYAUX5, "resources/boyaux5.wav");
  _instance->addSoundBuffer(BOYAUX6, "resources/boyaux6.wav");
  _instance->addSoundBuffer(CHAN1, "resources/chan1.wav");
  _instance->addSoundBuffer(CHAN2, "resources/chan2.wav");
  _instance->addSoundBuffer(CHAN3, "resources/chan3.wav");
  _instance->addSoundBuffer(DASH, "resources/dash.wav");
  _instance->addSoundBuffer(DESU1, "resources/desu1.wav");
  _instance->addSoundBuffer(DESU2, "resources/desu2.wav");
  _instance->addSoundBuffer(DESU3, "resources/desu3.wav");
  _instance->addSoundBuffer(EUUUH1, "resources/euuuh1.wav");
  _instance->addSoundBuffer(EUUUH2, "resources/euuuh2.wav");
  _instance->addSoundBuffer(KOREWA1, "resources/korewa1.wav");
  _instance->addSoundBuffer(KOREWA2, "resources/korewa2.wav");
  _instance->addSoundBuffer(MOBSPAWN1, "resources/mobspawn1.wav");
  _instance->addSoundBuffer(MOBSPAWN2, "resources/mobspawn2.wav");
  _instance->addSoundBuffer(MOBSPAWN3, "resources/mobspawn3.wav");
  _instance->addSoundBuffer(MOBSPAWN4, "resources/mobspawn4.wav");
  _instance->addSoundBuffer(MOBSPAWN5, "resources/mobspawn5.wav");
  _instance->addSoundBuffer(MOBSPAWN6, "resources/mobspawn6.wav");
  _instance->addSoundBuffer(NANI1, "resources/nani1.wav");
  _instance->addSoundBuffer(NANI2, "resources/nani2.wav");
  _instance->addSoundBuffer(PROUT, "resources/prout.wav");
  _instance->addSoundBuffer(SHOOT, "resources/shoot.wav");
  _instance->addSoundBuffer(WTSW1, "resources/watashiwa1.wav");
  _instance->addSoundBuffer(WTSW2, "resources/watashiwa2.wav");
  _instance->addSoundBuffer(WTSW3, "resources/watashiwa3.wav");
  _instance->boyaux = {{BOYAUX1, BOYAUX2, BOYAUX3, BOYAUX4, BOYAUX5, BOYAUX6}};
  _instance->euuuh = {{EUUUH1, EUUUH2}};
  _instance->mobspawn = {{MOBSPAWN1, MOBSPAWN2, MOBSPAWN3, MOBSPAWN4, MOBSPAWN5, MOBSPAWN6}};
  _instance->player_sounds = {{CHAN1, CHAN2, CHAN3, DESU1, DESU2, DESU3,
    KOREWA1, KOREWA2, NANI1, NANI2, WTSW1, WTSW2, WTSW3}};
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
