#ifndef INPUT_HPP_
# define INPUT_HPP_

# include <iostream>
# include <queue>
# include "my_opengl.hpp"

struct Key {
  int key;
  int scancode;
  int action;
  int mode;
};

struct Mouse {
  double x;
  double y;
};

struct Button {
  int button;
  int action;
  int mods;
};

struct Event
{
  bool hasEvent;
  enum {
    KEY,
    MOUSE,
    BUTTON,
  } type;

  GLFWwindow *window;

  union {
    Key key;
    Mouse mouse;
    Button button;
  } val;

  operator bool() const { return hasEvent; };
};

/**
 * Set callback with logic
 */
class Input
{
public:
  static Event pollEvent();
  static void setWindow(GLFWwindow *window);
  static bool isKeyPressed(int key);

private:
  Input() = default;

private:
  static Input instance;
  std::queue<Event> _events;
};

#endif /* !INPUT_HPP_ */
