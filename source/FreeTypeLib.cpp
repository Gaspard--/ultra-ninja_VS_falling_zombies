#include <exception>
#include "FreeTypeLib.hpp"
#include "display.hpp"

FreeTypeLib::FreeTypeLib(std::string fontFile)
  : face(nullptr)
{
  if (FT_Init_FreeType(&library))
    throw std::runtime_error("failed to init FreeType");
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
}

FreeTypeLib::~FreeTypeLib()
{
  FT_Done_FreeType(library);
}
