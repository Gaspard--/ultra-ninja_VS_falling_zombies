#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

#include <memory>

#include "vect.hpp"
#include "render_context.hpp"
#include "my_opengl.hpp"
#include "FreeTypeLib.hpp"

class Display
{
private:
  struct GlfwContext
  {
    GlfwContext();
    ~GlfwContext();
  } glfwContext;

  std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window;
  FreeTypeLib fontHandler;
public:
  Display();

  ~Display();

  bool render();
};

#endif
