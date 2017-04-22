#include <exception>
#include "FreeTypeLib.hpp"
#include "display.hpp"

display::FreeTypeLib::FreeTypeLib()
  : fontLoaded(false), face(nullptr)
{
  if (FT_Init_FreeType(&library))
    throw std::runtime_error("failed to init FreeType");
}

void display::FreeTypeLib::loadFont(std::string fontFile)
{
  if (face)
    FT_Done_Face(face);
  int error = FT_New_Face(library,
			   fontFile.c_str(),
			   0,
			   &face);
  if (error == FT_Err_Unknown_File_Format)
    throw std::runtime_error(fontFile + ": failed to load font, unsupported font type");
  else if (error)
    throw std::runtime_error(fontFile + ": failed to load font");
  FT_Set_Pixel_Sizes(face, 0, 64);
  fontLoaded = true;
}

void display::FreeTypeLib::renderText(std::string text, Vect<2u, float> pos, display::Display &display)
{
  if (!face)
    throw std::runtime_error("No font loaded to render text.");
  Vect<2u, float> pen(pos);

  for (auto it(text.begin()); it != text.end(); ++it)
    {
      FT_Load_Char(face, (FT_ULong)*it, FT_LOAD_RENDER);
      FT_GlyphSlot &slot = face->glyph;  /* a small shortcut */

      // TODO
      // display.renderBuffer(pen + Vect<2u, float>{slot->bitmap_left, -slot->bitmap_top + 64.0f} / 64.0f,
      // 			   {slot->bitmap.pitch, slot->bitmap.rows}, slot->bitmap.buffer);

      pen[0] += slot->advance.x / (64.0f * 64.0f);
    }
}

display::FreeTypeLib::~FreeTypeLib()
{
  FT_Done_FreeType(library);
}
