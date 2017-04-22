#ifndef RENDERABLE_HPP
# define RENDERABLE_HPP

# include "my_opengl.hpp"
# include "Vect.hpp"

struct Renderable
{
  Texture texture;

  // TEXTURE
  /// bottom left corner of source rect
  Vect<2u, float> sourcePos{0.0f, 0.0f};
  /// size of source rect
  Vect<2u, float> sourceSize{0.0f, 0.0f};

  // DISPLAY
  /// center of dest position
  Vect<2u, float> destPos{0.0f, 0.0f};
  /// size when displayed
  Vect<2u, float> destSize{0.0f, 0.0f};
};

#endif
