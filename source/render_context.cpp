#include "render_context.hpp"

void RenderContext::bind()
{
  glBindVertexArray(vao);
  glUseProgram(program);
}

void RenderContext::unbind()
{
  glBindVertexArray(0);
  glUseProgram(0);
}
