#ifndef RECT_HPP
# define RECT_HPP

# include "Vect.hpp"

struct  Rect
{
  Rect(const Vect<2, float>& i_pos, const Vect<2, float>& i_size, const Vect<4, float>& i_color):
    pos(i_pos),
    size(i_size),
    color(i_color) {}

  Vect<2, float>      pos;
  Vect<2, float>      size;
  Vect<4, float>      color;
};

#endif /* RECT_HPP */
