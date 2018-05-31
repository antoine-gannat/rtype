
#include "Core.hpp"
#include "Text.hpp"

Text::Text(int x, int y, std::string font_path)
{
  if (!font.loadFromFile(font_path))
    throw std::runtime_error("Failed to load font");
  text.setFont(font);
  text.setCharacterSize(CHARACTER_SIZE);
  text.setPosition(x, y);
}

Text::~Text()
{

}

