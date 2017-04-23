#ifndef GUI_HPP
# define GUI_HPP

# include "Rect.hpp"
# include <string>
# include <unordered_map>

class   Display;

class   GUI
{

public:

  enum class State {
    INACTIVE,
    OVERFLEW,
    ACTIVE
  };

  class Button
  {

  public:

    Button(const Rect& rect, const std::string str);

    bool        isOverflew(const Vect<2, float>&);
    void        draw(Display&);

  private:

    Rect                _rect;
    Vect<4, float>      _inactiveColor;
    Vect<4, float>      _overflewColor;
    std::string         _str;
    State               _state;
  };

  void  addElem(const std::string& key, const Button& elem);

  void  drawElems(Display&);

  std::string   haveElemPressed(const Vect<2, float>&, bool leftClick);

private:

  std::unordered_map<std::string, Button>       _stack;

};

#endif /* GUI_HPP */
