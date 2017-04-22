#include <stdexcept>
#include "my_opengl.hpp"

void my_opengl::shaderError(GLenum const shadertype, GLuint const shader)
{
  GLint	len;
  std::string log;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  log.reserve((unsigned int)len);
  glGetShaderInfoLog(shader, len, NULL, &log[0]);
  throw std::runtime_error(std::string("Compilation failed for ")
			   + ((shadertype == GL_VERTEX_SHADER) ?
			      "vertex" : (shadertype == GL_FRAGMENT_SHADER) ?
			      "fragment" : "unknown (fix this in my_opengl.cpp!)")
			   + std::string(" shader: ")
			   + log);
}

void my_opengl::setUniform(Vect<2, float> const data, char const *target, Program program)
{
  glUniform2f(glGetUniformLocation(program, target), data[0], data[1]);
}

void my_opengl::setUniform(int const data, char const *target, Program program)
{
  glUniform1i(glGetUniformLocation(program, target), data);
}

void my_opengl::programError(GLuint const program)
{
  GLint len;
  std::string log;

  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  log.reserve((unsigned int)len);
  glGetProgramInfoLog(program, len, NULL, &log[0]);
  throw std::runtime_error("link failure: " + log);
}

Shader my_opengl::createShader(GLenum const shadertype, GLchar const *src)
{
  Shader shader(shadertype);
  GLint status(0);

  glShaderSource(shader, 1, &src, (const GLint *)0);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    shaderError(shadertype, shader);
  return (shader);
}

Shader::Shader(GLuint shadertype)
  : shader(glCreateShader(shadertype)), count(new unsigned int(1u))
{
}

Shader::~Shader()
{
  if (!--*count)
    {
      glDeleteShader(shader);
      delete count;
    }
}

Shader::Shader(Shader const &s)
  : shader(s.shader), count(s.count)
{
  ++*count;
}

Shader &Shader::operator=(Shader s)
{
  std::swap(s.count, count);
  std::swap(s.shader, shader);
  return *this;
}

Shader::operator GLuint() const
{
  return shader;
}

Program::Program()
  : program(glCreateProgram()), count(new unsigned int(1u))
{
}

Program::~Program()
{
  if (!--*count)
    {
      glDeleteProgram(program);
      delete count;
    }
}

Program::Program(Program const &s)
  : program(s.program), count(s.count)
{
  ++*count;
}

Program &Program::operator=(Program s)
{
  std::swap(s.count, count);
  std::swap(s.program, program);
  return *this;
}

Program::operator GLuint() const
{
  return program;
}

Vao::Vao()
  : vao(0u), count(new unsigned int(1u))
{
  glGenVertexArrays(1, &vao);
}

Vao::~Vao()
{
  if (!--*count)
    {
      glDeleteVertexArrays(1, &vao);
      delete count;
    }
}

Vao::Vao(Vao const &s)
  : vao(s.vao), count(s.count)
{
  ++*count;
}

Vao &Vao::operator=(Vao s)
{
  std::swap(s.count, count);
  std::swap(s.vao, vao);
  return *this;
}

Vao::operator GLuint() const
{
  return vao;
}

glBuffer::glBuffer()
  : buffer(0u), count(new unsigned int(1u))
{
  glGenBuffers(1, &buffer);
}

glBuffer::~glBuffer()
{
  if (!--*count)
    {
      glDeleteBuffers(1, &buffer);
      delete count;
    }
}

glBuffer::glBuffer(glBuffer const &s)
  : buffer(s.buffer), count(s.count)
{
  ++*count;
}

glBuffer &glBuffer::operator=(glBuffer s)
{
  std::swap(s.count, count);
  std::swap(s.buffer, buffer);
  return *this;
}

glBuffer::operator GLuint() const
{
  return buffer;
}

Framebuffer::Framebuffer()
  : framebuffer(0u), count(new unsigned int(1u))
{
  glGenFramebuffers(1, &framebuffer);
}

Framebuffer::~Framebuffer()
{
  if (!--*count)
    {
      glDeleteFramebuffers(1, &framebuffer);
      delete count;
    }
}

Framebuffer::Framebuffer(Framebuffer const &s)
  : framebuffer(s.framebuffer), count(s.count)
{
  ++*count;
}

Framebuffer &Framebuffer::operator=(Framebuffer s)
{
  std::swap(s.count, count);
  std::swap(s.framebuffer, framebuffer);
  return *this;
}

Framebuffer::operator GLuint() const
{
  return framebuffer;
}

Texture::Texture()
  : texture(0u), count(new unsigned int(1u))
{
  glGenTextures(1, &texture);
}

Texture::~Texture()
{
  if (!--*count)
    {
      glDeleteTextures(1, &texture);
      delete count;
    }
}

Texture::Texture(Texture const &s)
  : texture(s.texture), count(s.count)
{
  ++*count;
}

Texture &Texture::operator=(Texture s)
{
  std::swap(s.count, count);
  std::swap(s.texture, texture);
  return *this;
}

Texture::operator GLuint() const
{
  return texture;
}
