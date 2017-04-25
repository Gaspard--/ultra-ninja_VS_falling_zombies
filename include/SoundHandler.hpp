#ifndef SOUNDHANDLER_HPP_
# define SOUNDHANDLER_HPP_

# include <map>
# include <memory>
# include <SFML/Audio.hpp>

class SoundHandler
{
public:

  enum SoundList
    {
      BOYAUX1,
      BOYAUX2,
      BOYAUX3,
      BOYAUX4,
      BOYAUX5,
      BOYAUX6,
      CHAN1,
      CHAN2,
      CHAN3,
      DASH,
      DESU1,
      DESU2,
      DESU3,
      EUUUH1,
      EUUUH2,
      KOREWA1,
      KOREWA2,
      MOBSPAWN1,
      MOBSPAWN2,
      MOBSPAWN3,
      MOBSPAWN4,
      MOBSPAWN5,
      MOBSPAWN6,
      NANI1,
      NANI2,
      PROUT,
      SHOOT,
      WTSW1,
      WTSW2,
      WTSW3,
    };

  static void initSoundHandler();
  static SoundHandler& getInstance();
  static void destroySoundHandler();

  void playMainMusic();
  void playSound(SoundList, int = 100);
  void deleteSounds();
  void addSoundBuffer(SoundList, std::string const&);
  sf::SoundBuffer* getSoundBuffer(SoundList) const;

  std::array<SoundList, 2> euuuh;
  std::array<SoundList, 6> boyaux;
  std::array<SoundList, 6> mobspawn;
  std::array<SoundList, 13> player_sounds;

private:

  SoundHandler();

  static std::unique_ptr<SoundHandler> _instance;

  sf::Music mainMusic;
  std::map<SoundList, sf::SoundBuffer*> _sound;
  std::vector<sf::Sound *> _soundsPlaying;
};

#endif /* !SOUNDHANDLER_HPP_ */
