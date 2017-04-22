#include <functional>
#include "Input.hpp"

/**
 * Set input callback
 * Using weird trick to compile with stateful closure
 */
Input::Input(GLFWwindow *window, Logic& logic) : _logic(logic)
{
  // KEY CALLBACK
  static KEY_CALLBACK keyFunc = [&] (GLFWwindow *window, int key, int scancode, int action, int mode) {
    keyCallback(window, key, scancode, action, mode);
  };
  auto handleKey = [] (GLFWwindow *window, int key, int scancode, int action, int mode) {
    keyFunc(window, key, scancode, action, mode);
  };

  // MOUSE CALLBACK
  static MOUSE_CALLBACK mouseFunc = [&] (GLFWwindow *window, double x, double y) {
    mouseCallback(window, x, y);
  };
  auto handleMouse = [] (GLFWwindow *window, double x, double y) {
    mouseFunc(window, x, y);
  };

  // MOUSE BUTTON CALLBACK
  static MOUSE_BUTTON_CALLBACK mouseButtonFunc = [&] (GLFWwindow *window, int button, int action, int mods) {
    mouseButtonCallback(window, button, action, mods);
  };
  auto handleMouseButton = [] (GLFWwindow *window, int button, int action, int mods) {
    mouseButtonFunc(window, button, action, mods);
  };

  glfwSetKeyCallback(window, handleKey);
  glfwSetCursorPosCallback(window, handleMouse);
  glfwSetMouseButtonCallback(window, handleMouseButton);
}

Input::~Input()
{

}


void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  (void)scancode;
  (void)mode;
  (void)action;
  switch (key)
    {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, true);
      break;
    }
}
void Input::mouseCallback(GLFWwindow *window, double x, double y)
{
  (void)window;
  std::cout << "x: " << x << "y: " << y << std::endl;
}
void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  (void)window;
  (void)button;
  (void)action;
  (void)mods;
}
