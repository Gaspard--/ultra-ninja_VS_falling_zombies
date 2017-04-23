#ifndef TEXTUREHANDLER_HPP_
# define TEXTUREHANDLER_HPP_

# include <map>
# include <memory>
# include "my_opengl.hpp"

class TextureHandler
{
  enum TextureList
    {
      BOYAUX,
      PLANET,
      SWORDRADIUS,
      TEST
    };

public :
  static void initTextureHandler();
  static TextureHandler& getInstance();
  static void destroyTextureHandler();

  void addTexture(TextureList, std::string);

private:

  TextureHandler();
  static std::unique_ptr<TextureHandler> _instance;
  std::map<TextureList, Texture> _textures;
};

#endif /* !TEXTUREHANDLER_HPP_ */
