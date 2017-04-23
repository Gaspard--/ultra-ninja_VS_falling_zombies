# include "GUI.hpp"
# include "display.hpp"

GUI::Button::Button(const Rect& rect, const std::string str) : _rect(rect), _inactiveColor(_rect.color), _overflewColor(_rect.color)
{
  _str = str;
  _overflewColor = Vect<4, float>(_inactiveColor[0] * 1.1,
                                  _inactiveColor[1] * 1.1,
                                  _inactiveColor[2] * 1.1,
                                  _inactiveColor[3]);
  for (unsigned int i = 0 ; i < 3 ; i++)
    if (_overflewColor[i] > 1)
      _overflewColor[i] = 1;
  _state = State::INACTIVE;
}

bool    GUI::Button::isOverflew(const Vect<2, float>& mouse)
{
  if (mouse.x() >= _rect.pos.x() && mouse.x() <= _rect.pos.x() + _rect.size.x() &&
      mouse.y() >= _rect.pos.y() && mouse.y() <= _rect.pos.y() + _rect.size.y())
    {
      _state = State::OVERFLEW;
      return (true);
    }
  _state = State::INACTIVE;
  return (false);
}

void    GUI::Button::draw(Display& disp)
{
  if (_state == State::INACTIVE)
    _rect.color = _inactiveColor;
  else if (_state == State::OVERFLEW)
    _rect.color = _overflewColor;
  disp.displayRect(_rect);
}

void    GUI::addElem(const std::string& key, const Button& elem)
{
  _stack.insert({key, elem});
}

std::string     GUI::haveElemPressed(const Vect<2, float>& mouse, bool leftClick)
{
  for (auto i = _stack.begin() ; i != _stack.end() ; ++i)
    if (i->second.isOverflew(mouse) && leftClick)
      return (i->first);
  return ("");
}

void    GUI::drawElems(Display& disp)
{
  for (auto i = _stack.begin() ; i != _stack.end() ; ++i)
    i->second.draw(disp);
}
