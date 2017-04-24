# include <iostream>
# include "display.hpp"
# include "Logic.hpp"
# include "TextureHandler.hpp"
# include "SoundHandler.hpp"
# include "Input.hpp"
# include <random>

int main()
{
  std::srand(time(NULL));
  try {
    Display& display = Display::getInstance();
    Input::setWindow(display.getWindow());

    struct SoundHandlerInit
    {
      SoundHandlerInit()
      {
        SoundHandler::initSoundHandler();
      }

      ~SoundHandlerInit()
      {
        SoundHandler::destroySoundHandler();
      }
    } SoundHandlerIniter;

    struct TextureHandlerInit
    {
      TextureHandlerInit()
      {
        TextureHandler::initTextureHandler();
      }

      ~TextureHandlerInit()
      {
        TextureHandler::destroyTextureHandler();
      }
    } textureHandlerIniter;

    struct LogicInit
    {
      LogicInit()
      {
        Logic::initLogic(10);
      }

      ~LogicInit()
      {
        Logic::destroyLogic();
      }
    } logicIniter;

    SoundHandler::getInstance().playMainMusic();
    while (display.isRunning())
      {
        // handle events
        for (Event ev = Input::pollEvent(); ev; ev = Input::pollEvent())
          Logic::getInstance().handleEvent(ev);
        Logic::getInstance().checkEvents(display);

        // update logic
        Logic::getInstance().tick();

        // render
        display.render(Logic::getInstance());
      }

  } catch (std::runtime_error const &e) {
    std::cerr << "program encoutered runtime error:" << std::endl
              << e.what() << std::endl;
    return -1;
  }
}
