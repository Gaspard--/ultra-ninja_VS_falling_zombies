#ifndef FREE_TYPE_LIB_HPP
# define FREE_TYPE_LIB_HPP

#include <string>
#include <functional>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Vect.hpp"
#include <iostream>

class Display;

class FreeTypeLib
{
private:
  FT_Library library;
  FT_Face face;
  char badPadding[8];
public:
  FreeTypeLib(std::string fontFile);
  FreeTypeLib(FreeTypeLib const &) = delete;
  ~FreeTypeLib();

  template<class A>
  void renderText(std::string text, A renderBuffer, unsigned int size, Vect<2u, float> step, Vect<2u, float> pos)
  {
    FT_Set_Pixel_Sizes(face, 0, size);
    Vect<2u, float> pen(pos);

    for (auto it(text.begin()); it != text.end(); ++it)
      {
	FT_GlyphSlot &slot(face->glyph);  /* a small shortcut */
	FT_Load_Char(face, (FT_ULong)*it, FT_LOAD_RENDER);
    	renderBuffer(((pen + Vect<2u, float>{slot->bitmap_left, slot->bitmap_top} / (float)size)) * step,
		     (Vect<2u, float>{slot->bitmap.pitch, slot->bitmap.rows} * step / (float)size)
		     , slot->bitmap.buffer);

	// std::cout << ((Vect<2u, float>{slot->bitmap.pitch, slot->bitmap.rows} / (float)size) * step
	// 	     )[1] << std::endl;
	pen[0] += (face->glyph->advance.x >> 8u) / (float)size;
      }
}

};

#endif
