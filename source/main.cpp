#include <iostream>
#include "display.hpp"
#include "Logic.hpp"
#include "Input.hpp"

int main()
{
  try {
    Logic logic;
    Display display;

    // init input with GLFW window
    Input::setWindow(display.getWindow());

    while (display.isRunning())
      {
	// handle events
	for (Event ev = Input::pollEvent(); ev; ev = Input::pollEvent())
	  logic.handleEvent(ev);

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
