#ifndef RENDER_CONTEXT_HPP
# define RENDER_CONTEXT_HPP

# include "my_opengl.hpp"

class RenderContext
{
public:
  Vao const vao;
  Program const program;
  //  Vect<TextureCount, GLuint> textures; TODO: textures

  void bind();
  void unbind();
};

#endif // !RENDER_CONTEXT_HPP
