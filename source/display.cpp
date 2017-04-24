#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "display.hpp"
#include "bind.hpp"

Display Display::instance{};

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

Display& Display::getInstance()
{
  return instance;
}

Display::Display()
  : window([this]{
      std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(1920, 1080, "ultra-ninja VS falling zombies", nullptr, nullptr), &glfwDestroyWindow);

      if (!window)
        throw std::runtime_error("opengl: failed to open window");
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
  , planet(my_opengl::loadTexture("resources/PlanetRed.bmp"))
  , bloodSpray{my_opengl::loadTexture("resources/BloodSpray.bmp"), my_opengl::loadTexture("resources/BloodSpray2.bmp"), my_opengl::loadTexture("resources/BloodSpray3.bmp")}
  , mobSpray{my_opengl::loadTexture("resources/MobSpray.bmp"), my_opengl::loadTexture("resources/MobSpray2.bmp"), my_opengl::loadTexture("resources/MobSpray3.bmp")}
  , planetRenderTexture({1024, 1024})
  , camera{0, 1.0}
  , dim{0, 0}
  , size{0, 0}
{
  static auto setFrameBuffer =
    [this] (int width, int height)
    {
      glViewport(0, 0, width, height);
      size = {width, height};
      dim = {height / (float)width, 1.0};
    };

  glfwSetFramebufferSizeCallback(window.get(), [] (GLFWwindow *, int width, int height) {
      setFrameBuffer(width, height);
    });

  {
    Bind<RenderContext> bind(textureContext);

    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
  }
  {
    Bind<RenderContext> bind(rectContext);

    glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
  }
  {
    Bind<RenderContext> bind(textContext);

    glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), reinterpret_cast<void *>(2u * sizeof(float)));
  }
  {
    glBindFramebuffer(GL_FRAMEBUFFER, planetRenderTexture.framebuffer);
    glViewport(0, 0, 1024, 1024);
    glClearColor(0.2, 0.2, 0.5, 0.2);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    {
      Vect<2u, float> olddim(dim);

      dim = {1.0, 1.0};
      displayPlanet(planet, 2.0, {1.0, 0.0});
      dim = olddim;
    }
    glDisable(GL_BLEND);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

void Display::displayText(std::string const &text, unsigned int fontSize, Vect<2u, float> step, Vect<2u, float> textPos, Vect<2u, float> rotation, Vect<3u, float> color)
{
  fontHandler.renderText(text, [this, textPos, rotation, color](Vect<2u, float> pen, Vect<2u, float> size, unsigned char *buffer, Vect<2u, int> fontDim)
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
                                        (GLsizei)(fontDim[0]),
                                        (GLsizei)(fontDim[1]),
                                        0,
                                        GL_RED,
                                        GL_UNSIGNED_BYTE,
                                        static_cast<void *>(buffer));
                           float data[16];

                           for (unsigned int i(0); !(i & 4u); ++i)
                             {
                               Vect<2u, float> corner{i & 1u, i >> 1u};
                               Vect<2u, float> destCorner(rotate(pen + textPos + corner * size, rotation));

                               data[i * 4 + 0] = corner[0];
                               data[i * 4 + 1] = 1.0 - corner[1];
                               data[i * 4 + 2] = destCorner[0];
                               data[i * 4 + 3] = destCorner[1];
                             }
                           glBindBuffer(GL_ARRAY_BUFFER, textBuffer);
                           glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
                           my_opengl::setUniform(dim, "dim", textContext.program);
                           my_opengl::setUniform(color, "textColor", textContext.program);
                           my_opengl::setUniform(0u, "tex", textContext.program);
                           glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                         }, fontSize, step);
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
  my_opengl::setUniform(dim, "dim", rectContext.program);
  my_opengl::setUniform(rect.color, "rect_color", rectContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void    Display::displayInterface(void)
{
  Logic logic = Logic::getInstance();
  int   size = (std::to_string(logic.getRemainingsSpace()) + "/" + std::to_string(logic.getMaxMobs())).size();

  displayText(std::to_string(logic.getRemainingsSpace()) + "/" + std::to_string(logic.getMaxMobs()),
              256, {0.2f, 0.2f}, {-0.08f * size, -0.3f}, {sqrt(camera.length2()), 0}, {1.0, 0.0, 0.5});
  displayText("Score   " + std::to_string(logic.getScore()), 256, {0.1f, 0.1f}, {-1.8, 0.72}, {1, 0}, {1.0, 1.0, 0.5});
  displayText("Time   " + logic.getTime(), 256, {0.1f, 0.1f}, {-1.8, 0.5}, {1, 0}, {1.0, 0.5, 1.0});
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
  my_opengl::setUniform(dim, "dim", textureContext.program);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::drawBlood(Vect<2u, float> rotation, Texture texture)
{
  glBindFramebuffer(GL_FRAMEBUFFER, planetRenderTexture.framebuffer);
  glViewport(0, 0, 1024, 1024);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  displayPlanet(texture, 2.0, rotation);
  // {
  //   Bind<RenderContext> bind(textureContext);
  //   float buffer[4u * 4u];

  //   for (unsigned int j(0u); j != 4u; ++j)
  //     {
  // 	Vect<2u, float> const corner((j & 1u), (j >> 1u));
  // 	Vect<2u, float> const destCorner(rotate((corner - Vect<2u, float>{0.5f, 0.5f}) * 2.0, rotation));

  // 	std::copy(&corner[0u], &corner[2u], &buffer[j * 4u]);
  // 	std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
  //     }
  //   glActiveTexture(GL_TEXTURE0);
  //   glBindTexture(GL_TEXTURE_2D, blood);
  //   glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  //   my_opengl::setUniform(dim, "dim", textureContext.program);
  //   my_opengl::setUniform(0u, "tex", textureContext.program);
  //   glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  //   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, size[0], size[1]);
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
      Vect<2u, float> const destCorner(rotate(renderable.destPos + (rotate((corner - Vect<2u, float>{0.5f, 0.5f})
                                                                           * renderable.destSize, {up[1], -up[0]})), rotation));

      std::copy(&sourceCorner[0u], &sourceCorner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderable.texture);
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  my_opengl::setUniform(dim, "dim", textureContext.program);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::displayEntityWithSpeed(Entity const& e, Vect<2u, float> rotation)
{
  Bind<RenderContext> bind(textureContext);
  float buffer[4u * 4u];
  Vect<2u, float> up(e.fixture.speed.normalized());

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner((j & 1u), (j >> 1u));
      Vect<2u, float> const sourceCorner(e.renderable.sourcePos + corner * e.renderable.sourceSize);
      Vect<2u, float> const destCorner(rotate(e.renderable.destPos + (rotate((corner - Vect<2u, float>{0.5f, 0.5f})
                                                                           * e.renderable.destSize, {up[1], -up[0]})), rotation));

      std::copy(&sourceCorner[0u], &sourceCorner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, e.renderable.texture);
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  my_opengl::setUniform(dim, "dim", textureContext.program);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::displayRenderableAsHUD(Renderable const& renderable)
{
  Bind<RenderContext> bind(textureContext);
  float buffer[4u * 4u];
  Vect<2u, float> const up(renderable.destPos.normalized());

  for (unsigned int j(0u); j != 4u; ++j)
    {
      Vect<2u, float> const corner((j & 1u), (j >> 1u));
      Vect<2u, float> const sourceCorner(renderable.sourcePos + corner * renderable.sourceSize);
      Vect<2u, float> const destCorner(renderable.destPos + (corner - Vect<2u, float>{0.5f, 0.5f}));

      std::copy(&sourceCorner[0u], &sourceCorner[2u], &buffer[j * 4u]);
      std::copy(&destCorner[0u], &destCorner[2u], &buffer[j * 4u + 2u]);
    }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderable.texture);
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  my_opengl::setUniform(dim, "dim", textureContext.program);
  my_opengl::setUniform(0u, "tex", textureContext.program);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Display::render(Logic const &logic)
{
  camera = camera * 0.8 + ((rotate(logic.getPlayerPos() / logic.getPlayerPos().length2()
                                   * Vect<2u, float>{1.0f, -1.0f}, {0.0f, 1.0f}) * 0.4f)) * 0.2;
  {
    Vect<2u, float> olddim(dim);

    dim = {1.0, 1.0};
    glEnable(GL_BLEND);
    logic.for_each_flesh([this](auto const &flesh)
			 {
			   if (flesh->entity.isOnPlanet)
			     this->drawBlood(rotate(flesh->entity.fixture.pos.normalized(), Vect<2u, float>{0, -1.0}), bloodSpray[rand() % 3]);
			 });
    logic.for_each_enemy([this](auto const &enemy)
			 {
			   if (enemy->entity.isOnPlanet && rand() % 10 == 0)
			     this->drawBlood(rotate(enemy->entity.fixture.pos.normalized(), Vect<2u, float>{0, -1.0}), mobSpray[rand() % 3]);
			 });
    glDisable(GL_BLEND);
    dim = olddim;
  }
  glClearColor(0.2, 0.2, 0.2, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  displayPlanet(planetRenderTexture.texture, logic.getPlanetSize(), camera);
  logic.for_each_entity([this, logic](auto const &e)
                        {
                          this->displayRenderable(e->renderable, camera);
                        });
  logic.for_each_projectile([this, logic](auto const &e)
                            {
                              this->displayEntityWithSpeed(*e, camera);
                            });
  displayInterface();
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

Vect<2u, float> Display::getCamera() const
{
  return camera;
}

Vect<2u, float> Display::getDim() const
{
  return dim;
}

Vect<2u, float> Display::getSize() const
{
  return size;
}
