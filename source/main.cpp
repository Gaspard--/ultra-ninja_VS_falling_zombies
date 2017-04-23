# include <iostream>
# include "display.hpp"
# include "Logic.hpp"
# include "Input.hpp"
# include <random>

int main()
{
  std::srand(time(NULL));
  try {
    Display display;
    Logic logic;

    // init input with GLFW window
    Input::setWindow(display.getWindow());
    while (display.isRunning())
      {
        // handle events
        for (Event ev = Input::pollEvent(); ev; ev = Input::pollEvent())
          logic.handleEvent(ev);
        logic.checkEvents(display);

        // update logic
        logic.tick();

        // render
        display.render(logic);
      }

  } catch (std::runtime_error const &e) {
    std::cerr << "program encoutered runtime error:" << std::endl
              << e.what() << std::endl;
    return -1;
  }
}
