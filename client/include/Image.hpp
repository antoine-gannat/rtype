#pragma once

class Image
{
protected:
  sf::Texture* texture;
public:
  sf::Sprite sprite;
  Image(std::string path, float ratio = 0.1);
  void draw();
  virtual ~Image();
};
