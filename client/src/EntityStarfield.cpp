#include "EntityStarfield.hpp"

EntityStarfield::EntityStarfield() :
  img("./assets/textures/starfield.png"), _scrollState(0)
{
  _id = -2;
  img.sprite.setScale(1, 1);
}

EntityStarfield::~EntityStarfield()
{
}

void EntityStarfield::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityStarfield::getPos() const
{
  return img.sprite.getPosition();
}

void EntityStarfield::update()
{
  _scrollState += 5;
  if (_scrollState >= 3750)
    _scrollState -= 3750;
  img.sprite.setTextureRect(sf::IntRect(_scrollState, 0, 1600, 900));
  img.draw();
}
