
#include <map>
#include "Core.hpp"
#include "Image.hpp"

Image::Image(std::string path, float ratio)
{
  static std::map<std::string, sf::Texture*> loaded;
  texture = new sf::Texture();
  
  if (loaded.find(path) == loaded.end()) {
    if (!texture->loadFromFile(path))
      throw std::runtime_error("Can't load asset");
    loaded.insert(std::make_pair(path, texture));
    std::cout << "Loaded: " << path << std::endl;
  }
  else {
    texture = loaded[path];
  }
  sprite = sf::Sprite(*texture);
  sprite.setScale((float)CORE->width / sprite.getGlobalBounds().width * ratio,
  		  (float)CORE->height / sprite.getGlobalBounds().height * ratio);
}

void Image::draw()
{
  CORE->window.draw(sprite);
}

Image::~Image()
{
}
