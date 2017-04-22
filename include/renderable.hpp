#ifndef RENDERABLE_HPP
# define RENDERABLE_HPP

# include "my_opengl.hpp"
# include "Vect.hpp"

struct Renderable
{
  Texture texture;
  /// bottom left corner of source rect
  Vect<2u, float> sourcePos;
  /// size of source rect
  Vect<2u, float> sourceSize;
  /// center of dest position
  Vect<2u, float> destPos;
  /// size when displayed
  Vect<2u, float> destSize;
};

#endif
