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
      mainMusic
    };

  static void initSoundHandler();
  static SoundHandler& getInstance();
  static void destroySoundHandler();

  void addSound(SoundList, std::string const&);
  sf::Sound getSound(SoundList) const;

private:

  SoundHandler();
  static std::unique_ptr<SoundHandler> _instance;
  std::map<SoundList, sf::Sound> _sound;
};

#endif /* !SOUNDHANDLER_HPP_ */
