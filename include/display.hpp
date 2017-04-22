#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

#include <memory>

#include "vect.hpp"
#include "render_context.hpp"
#include "my_opengl.hpp"
#include "FreeTypeLib.hpp"
#include "renderable.hpp"

class Display
{
private:
  struct GlfwContext
  {
    GlfwContext();
    ~GlfwContext();
  } glfwContext;

  std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window;
  FreeTypeLib fontHandler;
  RenderContext textureContext;
  glBuffer textureBuffer;
  Texture test;
public:
  Display();

  ~Display();

  /**
   * Displays a renderable in the world.
   * Optional rotation argument rotates the renderable around 0, 0
   * (for most elements this should be the position of the player * {1, -1})
   * See Renderable for details on how renderables are rendered
   */
  void displayRenderable(Renderable const renderable, Vect<2u, float> const rotation = {1.0, 0.0});

  bool render();
};

#endif
