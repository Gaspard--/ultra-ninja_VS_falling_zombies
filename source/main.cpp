#include <iostream>
#include "display.hpp"

int main()
{
  try {
    Display display;

    while (display.render());
  } catch (std::runtime_error const &e) {
    std::cerr << "program encoutered runtime error:" << std::endl
	      << e.what() << std::endl;
  }
}
