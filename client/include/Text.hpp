#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Text
{
protected:
  sf::Font font;
public:
  sf::Text text;
public:
  Text(int x, int y, std::string font_path = "assets/arial.ttf");
  virtual ~Text();
};
