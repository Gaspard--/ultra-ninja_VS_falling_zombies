#ifndef TEXTUREHANDLER_HPP_
# define TEXTUREHANDLER_HPP_

# include <memory>

class TextureHandler
{
public :
  static void initTextureHandler();
  static TextureHandler& getInstance();
  static void destroyTextureHandler();

private:

  static std::unique_ptr<TextureHandler> _instance;
  TextureHandler();
};

#endif /* !TEXTUREHANDLER_HPP_ */
