#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

#include <memory>

#include "Logic.hpp"
#include "Vect.hpp"
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
public:
  Display();

  ~Display();

  GLFWwindow *getWindow() const;

  void displayRect();

  void displayPlanet(Texture texture, float size, Vect<2u, float> rotation);

  /**
   * Displays a renderable in the world.
   * Optional rotation argument rotates the renderable around 0, 0
   * (for most world elements this should be the position of the player * {1, -1})
   * See Renderable for details on how renderables are rendered
   * This function is not suitable to render GUI
   */
  void displayRenderable(Renderable const& renderable, Vect<2u, float> rotation = {1.0, 0.0});

  void render(Logic const &);
  bool isRunning();
  Texture test;
};

#endif
