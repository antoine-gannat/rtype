#include "EntityShip.hpp"

int EntityShip::index = 0;

EntityShip::EntityShip() :
  nokey(true)
{
  _id = index;
  img = new Image("./assets/textures/Ships.png");
  img->sprite.setTextureRect(sf::IntRect(34, 17 * (_id % 4), 34, 17));
  img->sprite.setScale({3, 3});
  index++;
}

EntityShip::~EntityShip()
{
  delete img;
}

void EntityShip::setPos(sf::Vector2f pos)
{
  img->sprite.setPosition(pos);
}

sf::Vector2f EntityShip::getPos() const
{
  return img->sprite.getPosition();
}

void EntityShip::update()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      img->sprite.setTextureRect(sf::IntRect(68, 17 * (_id % 4), 34, 16));
      nokey = false;
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      img->sprite.setTextureRect(sf::IntRect(0, 17 * (_id % 4), 34, 16));
      nokey = false;
    }
  if (nokey)
    img->sprite.setTextureRect(sf::IntRect(34, 17 * (_id % 4), 34, 16));
  nokey = true;
  img->draw();
}
