#ifndef FREE_TYPE_LIB_HPP
# define FREE_TYPE_LIB_HPP

#include <string>
#include <functional>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Vect.hpp"

class Display;

class FreeTypeLib
{
  FT_Library library;
  bool fontLoaded;
  FT_Face face;
  char badPadding[8];
public:
  FreeTypeLib();
  FreeTypeLib(FreeTypeLib const &) = delete;
  ~FreeTypeLib();
  void loadFont(std::string fontFile);
  void renderText(std::string text, Vect<2u, float> pos, Display &display);
};

#endif
