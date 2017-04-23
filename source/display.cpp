#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "display.hpp"
#include "bind.hpp"

inline RenderContext contextFromFiles(std::string name)
{
  std::stringstream vert;
  std::stringstream frag;
  std::ifstream vertInput("shaders/" + name + ".vert");
  std::ifstream fragInput("shaders/" + name + ".frag");

  if (!fragInput || !vertInput)
    throw std::runtime_error("lol");
  vert << vertInput.rdbuf();
  frag << fragInput.rdbuf();
  return {Vao(), my_opengl::createProgram<2>({GL_VERTEX_SHADER, GL_FRAGMENT_SHADER},
                                             {vert.str(), frag.str()})};
}

inline void framebufferSizeCallback(GLFWwindow *, int width, int height)
{
  glViewport((width - height) / 2, 0, height, height);
}

Display::GlfwContext::GlfwContext()
{
  glfwSetErrorCallback([](int, char const *str)
		       {
			 throw std::runtime_error(str);
		       });
  if (!glfwInit())
    throw std::runtime_error("opengl: failed to initialize glfw");
}

Display::GlfwContext::~GlfwContext()
{
  glfwTerminate();
}

Display::Display()
  : window([]{
      std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(1920, 1080, "ultra-ninja VS falling zombies", nullptr, nullptr), &glfwDestroyWindow);

      if (!window)
	throw std::runtime_error("opengl: failed to open window");
      glfwSetFramebufferSizeCallback(window.get(), &framebufferSizeCallback);
      glfwMakeContextCurrent(window.get());
      glfwSwapInterval(1);
      if (gl3wInit())
	throw std::runtime_error("opengl: failed to initialize 3.0 bindings");
      if (!gl3wIsSupported(3, 0))
	throw std::runtime_error("opengl: Opengl 3.0 not supported");
      return window;
    }())
  , fontHandler("resources/ObelixPro-Broken-cyr.ttf")
  , textureContext(contextFromFiles("texture"))
  , textContext(contextFromFiles("text"))
  , planet(my_opengl::loadTexture("resources/planet.bmp"))
{
  {
    Bind<RenderContext> bind(textureContext);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
  }
  {
    Bind<RenderContext> bind(rectContext);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
  }
  {
    Bind<RenderContext> bind(textContext);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
  }
}

Display::~Display()
{
}

GLFWwindow *Display::getWindow() const {
  return window.get();
}

static Vect<2u, float> rotate(Vect<2u, float> a, Vect<2u, float> b)
{
  return {a[0] * b[0] - a[1] * b[1], a[0] * b[1] + a[1] * b[0]};
}

void Display::displayText(std::string const &text, unsigned int fontSize, Vect<2u, float> step, Vect<2u, float> textPos)
{
  fontHandler.renderText(text, [this, fontSize, step](Vect<2u, float> pos, Vect<2u, int> dim, unsigned char *buffer)
			 {
			   Texture texture;
			   Bind<RenderContext> bind(textContext);

			   glActiveTexture(GL_TEXTURE0);
			   glBindTexture(GL_TEXTURE_2D, texture);
			   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			   glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RED,
					(GLsizei)(dim[0]),
					(GLsizei)(dim[1]),
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					static_cast<void *>(buffer));
			   float data[16];

			   for (unsigned int i(0); !(i & 4u); ++i)
			     {
			       Vect<2u, float> corner{i & 1u, i >> 1u};
			       Vect<2u, float> destCorner(Vect<2u, float>(pos) + corner * Vect<2u, float>(dim));

			       data[i * 4 + 0] = corner[0];
			       data[i * 4 + 1] = corner[1];
			       data[i * 4 + 2] = destCorner[0];
			       data[i * 4 + 3] = destCorner[1];
			       std::cout << destCorner[0] << ", " << destCorner[1] << std::endl;
			     }
			   glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
			   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			   glEnable(GL_BLEND);
			   my_opengl::setUniform(0u, "tex", textureContext.program);
			   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			   glBindTexture(GL_TEXTURE_2D, 0);
			   glDisable(GL_BLEND);
			 }, fontSize, step, textPos);
}

void Display::displayRect(Rect const &rect)
{
  Bind<RenderContext> bind(rectContext);
  float buffer[4u * 4u];

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner((j & 1u), (j >> 1u));
      Vect<2u, float> const destCorner(corner * rect.size + rect.pos);

      std::copy(&corner[0u], &corner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
  my_opengl::setUniform(rect.color, "rect_color", rectContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::displayPlanet(Texture texture, float size, Vect<2u, float> rotation)
{
  Bind<RenderContext> bind(textureContext);
  float buffer[4u * 4u];

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner((j & 1u), (j >> 1u));
      Vect<2u, float> const destCorner(rotate((corner - Vect<2u, float>{0.5f, 0.5f}) * size, rotation));

      std::copy(&corner[0u], &corner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::displayRenderable(Renderable const& renderable, Vect<2u, float> rotation)
{
  Bind<RenderContext> bind(textureContext);
  float buffer[4u * 4u];
  Vect<2u, float> up(renderable.destPos.normalized());

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner((j & 1u), (j >> 1u));
      Vect<2u, float> const sourceCorner(renderable.sourcePos + corner * renderable.sourceSize);
      Vect<2u, float> const destCorner(rotate(renderable.destPos + (rotate((corner - Vect<2u, float>{0.5f, 0.5f}) * renderable.destSize, {up[1], -up[0]})), rotation));

      std::copy(&sourceCorner[0u], &sourceCorner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderable.texture);
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::render(Logic const &logic)
{
  glClearColor(0.2, 0.2, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  displayPlanet(planet, logic.getPlanetSize(), {1.0, 0.0});
  logic.for_each_entity([this](auto const &e)
			{
			  this->displayRenderable(e->renderable);
			});
  displayText("lol MDR", 128, {0.1f, 0.1f}, {0.1f, 0.1f});
  glDisable(GL_BLEND);

  glfwSwapBuffers(window.get());
  glfwPollEvents();
}

bool Display::isRunning() const
{
  return (!glfwWindowShouldClose(window.get()));
}

bool Display::isKeyPressed(int key) const
{
  return glfwGetKey(window.get(), key);
}
