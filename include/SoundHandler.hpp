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

    };

  static void initSoundHandler();
  static SoundHandler& getInstance();
  static void destroySoundHandler();

  void playMainMusic();
  void addSound(SoundList, std::string const&);
  sf::SoundBuffer* getSound(SoundList) const;

private:

  SoundHandler();

  static std::unique_ptr<SoundHandler> _instance;

  sf::Music mainMusic;
  std::map<SoundList, sf::SoundBuffer*> _sound;
};

#endif /* !SOUNDHANDLER_HPP_ */
