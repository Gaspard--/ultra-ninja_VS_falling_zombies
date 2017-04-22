#include <iostream>
#include "display.hpp"
#include "Logic.hpp"
#include "Input.hpp"

int main()
{
  try {
    Logic logic;
    Display display;
    Input input(display.getWindow(), logic);

    while (display.isRunning())
      {
	logic.tick();
	display.render(logic);
      }
  } catch (std::runtime_error const &e) {
    std::cerr << "program encoutered runtime error:" << std::endl
	      << e.what() << std::endl;
  }
}
