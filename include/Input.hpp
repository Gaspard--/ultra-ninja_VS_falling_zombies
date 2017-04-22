#ifndef INPUT_HPP_
# define INPUT_HPP_

# include <my_opengl.hpp>
# include <iostream>
# include "Logic.hpp"

/**
 * Set callback with logic
 */
class Input
{
public:
  Input(GLFWwindow *window, Logic& logic);
  ~Input();

private:
  typedef std::function<void(GLFWwindow *window, int key, int scancode, int action, int mode)> KEY_CALLBACK;
  typedef std::function<void(GLFWwindow *window, double x, double y)> MOUSE_CALLBACK;
  typedef std::function<void(GLFWwindow *window, int button, int action, int mods)> MOUSE_BUTTON_CALLBACK;

  void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
  void mouseCallback(GLFWwindow *window, double x, double y);
  void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

private:
  Logic& _logic;
};

#endif /* !INPUT_HPP_ */
