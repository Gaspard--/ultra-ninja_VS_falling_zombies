#include <fstream>
#include <stdexcept>
#include "display.hpp"
#include "bind.hpp"

static void errorCallback(int, const char *str)
{
  throw std::runtime_error(str);
}

Display::GlfwContext::GlfwContext()
{
  glfwSetErrorCallback(&errorCallback);
  if (!glfwInit())
    throw std::runtime_error("opengl: failed to initialize glfw");
}

Display::GlfwContext::~GlfwContext()
{
  glfwTerminate();
}

static std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> createWindow()
{
  std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(1920, 1080, "Arcade", NULL, NULL), &glfwDestroyWindow);
  if (!window)
    throw std::runtime_error("opengl: failed to open window");
  glfwMakeContextCurrent(window.get());
  glfwSwapInterval(1);
  if (gl3wInit())
    throw std::runtime_error("opengl: failed to initialize 3.0 bindings");
  if (!gl3wIsSupported(3, 0))
    throw std::runtime_error("opengl: Opengl 3.0 not supported");
  return window;
}

Display::Display()
  : window(createWindow())
{
}

Display::~Display()
{
}


bool Display::render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window.get());
  glfwPollEvents();
  return (!glfwWindowShouldClose(window.get()));
}
