#include <functional>
#include "Input.hpp"

Input Input::instance = Input();

void Input::setWindow(GLFWwindow *window)
{
  // set glfw callback
  glfwSetKeyCallback(window, [] (GLFWwindow *window, int key, int scancode, int action, int mode) {
      Event ev = {true, Event::KEY, window, {.key = {key, scancode, action, mode}}};
      Input::instance._events.push(ev);
    });
  glfwSetCursorPosCallback(window, [] (GLFWwindow *window, double x, double y) {
      Event ev = {true, Event::MOUSE, window, {.mouse = {x, y}}};
      Input::instance._events.push(ev);
    });
  glfwSetMouseButtonCallback(window, [] (GLFWwindow *window, int button, int action, int mods) {
      Event ev = {true, Event::BUTTON, window, {.button = {button, action, mods}}};
      Input::instance._events.push(ev);
    });
}

Event Input::pollEvent()
{
  if (Input::instance._events.empty())
    {
      Event ev;
      ev.hasEvent = false;
      return ev;
    }

  Event event = Input::instance._events.front();

  Input::instance._events.pop();

  return event;
}
