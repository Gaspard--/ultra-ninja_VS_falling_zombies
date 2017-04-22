#ifndef INPUT_HPP_
# define INPUT_HPP_

# include <my_opengl.hpp>
# include <iostream>
# include <queue>
# include "Logic.hpp"

struct Event
{
  bool hasEvent;
  enum {
    KEY,
    MOUSE,
    BUTTON,
  } type;

  union {
    struct {
      int key;
      int scancode;
      int action;
      int mode;
    } key;
    struct {
      double x;
      double y;
    } mouse;
    struct {
      int button;
      int action;
      int mods;
    } button;
  } val;

  operator bool() { return hasEvent; };
};

/**
 * Set callback with logic
 */
class Input
{
public:
  static Event pollEvent();
  static void setWindow(GLFWwindow *window);

private:
  Input() = default;

private:
  static Input instance;
  std::queue<Event> _events;
};

#endif /* !INPUT_HPP_ */
