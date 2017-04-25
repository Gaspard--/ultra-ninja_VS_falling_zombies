#include <stdexcept>
#include <fstream>
#include <memory>
#include <iostream>
#include <sstream>
#include "my_opengl.hpp"

void my_opengl::shaderError(GLenum const shadertype, GLuint const shader)
{
  GLint	len;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  std::unique_ptr<GLchar[]> log(new GLchar[len + 1]);

  log[len + 1] = 0; // safety
  glGetShaderInfoLog(shader, len, nullptr, &log[0]);
  throw std::runtime_error(std::string("Compilation failed for ")
			   + ((shadertype == GL_VERTEX_SHADER) ?
			      "vertex" : (shadertype == GL_FRAGMENT_SHADER) ?
			      "fragment" : "unknown (fix this in my_opengl.cpp!)")
			   + std::string(" shader: ")
			   + &log[0]);
}

void my_opengl::setUniform(Vect<2, float> const data, char const *target, Program program)
{
  glUniform2f(glGetUniformLocation(program, target), data[0], data[1]);
}

void my_opengl::setUniform(Vect<3, float> const data, char const *target, Program program)
{
  glUniform3f(glGetUniformLocation(program, target), data[0], data[1], data[2]);
}

void my_opengl::setUniform(Vect<4, float> const data, char const *target, Program program)
{
  glUniform4f(glGetUniformLocation(program, target), data[0], data[1], data[2], data[3]);
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

Texture my_opengl::loadTexture(std::string const &name)
{
  auto bytesToInt = [](unsigned char *bytes)
    {
      return ((unsigned)bytes[3] << 24u)
      | ((unsigned)bytes[2] << 16u)
      | ((unsigned)bytes[1] << 8u)
      | (unsigned)bytes[0];
    };
  std::ifstream file(name, std::ios::binary);

  if (!file)
    throw std::runtime_error("'" + name + "': failed to open");
  file.exceptions(std::ios::badbit);

  unsigned char                 readBuf[4];
  Vect<2u, unsigned int>        dim{0, 0};
  try {
    file.seekg(10);
    file.read((char *)readBuf, sizeof(readBuf));
    unsigned int offset(bytesToInt(readBuf));

    file.seekg(14);
    file.read((char *)readBuf, sizeof(readBuf));

    file.read((char *)readBuf, sizeof(readBuf));
    dim[0] = bytesToInt(readBuf);

    file.read((char *)readBuf, sizeof(readBuf));
    dim[1] = bytesToInt(readBuf);

    file.seekg(offset);

    std::unique_ptr<unsigned char[]> data(new unsigned char[dim[0] * dim[1] * sizeof(unsigned int)]);

    file.read(reinterpret_cast<char *>(&data[0]), std::streamsize(dim[0] * dim[1] * sizeof(unsigned int)));

    std::streamsize r(file.gcount());

    if (r != std::streamsize(dim[0] * dim[1] * sizeof(unsigned int)))
      {
	std::stringstream s;

	s << name << ": file seems truncated, " << r << std::string(" bytes read.");
	throw std::runtime_error(s.str());
      }
    file.exceptions(std::ios::goodbit);

    // {
    //   Vect<2u, int> i{0, 0};

    //   for (i[0] = 0; i[0] < dim[0]; ++i[0])
    //     for (i[1] = 0; i[1] < (dim[1] >> 1u); ++i[1])
    //       {
    //         unsigned int sourcePos(i[0] + (dim[1] - i[1] - 1) * dim[0]);
    //         unsigned int destPos(i[0] + i[1] * dim[0]);

    //         std::swap(data[sourcePos * 4 + 0], data[destPos * 4 + 0]);
    //         std::swap(data[sourcePos * 4 + 1], data[destPos * 4 + 1]);
    //         std::swap(data[sourcePos * 4 + 2], data[destPos * 4 + 2]);
    //         std::swap(data[sourcePos * 4 + 3], data[destPos * 4 + 3]);
    //       }
    // }

    for (auto it = &data[0]; it < &data[dim[0] * dim[1] * sizeof(unsigned int)]; it += sizeof(unsigned int))
      {
        std::swap(it[0], it[3]);
        std::swap(it[1], it[2]);
      }
    Texture texture;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 (GLsizei)(dim[0]),
                 (GLsizei)(dim[1]),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 static_cast<void *>(data.get()));
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
  } catch (std::exception const &e) {
    throw std::runtime_error(name + ": failed to load texture(" + std::string(e.what()) + ")");
  }
}
