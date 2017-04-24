#ifndef RENDER_TEXTURE_HPP
# define RENDER_TEXTURE_HPP

# include <iostream>
# include "my_opengl.hpp"

class RenderTexture
{
public:
  Framebuffer framebuffer;
  Texture texture;

  RenderTexture(Vect<2u, unsigned int> const size);
};

#endif // !RENDER_TEXTURE_HPP
