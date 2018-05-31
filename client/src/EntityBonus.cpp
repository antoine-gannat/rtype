#include "EntityBonus.hpp"

EntityBonus::EntityBonus() : _anim(17, 18), img("./assets/textures/powerup.png")
{
  img.sprite.setScale({3, 3});
  for (int i = 0; i < 12/*nb frames*/ ; i++)
    {
      _anim.addFrame(i, sf::seconds(0.05));
    }
}

EntityBonus::~EntityBonus()
{
}

void EntityBonus::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityBonus::getPos() const
{
  return img.sprite.getPosition();
}

void EntityBonus::update()
{
  img.sprite.setTextureRect(_anim.getFrame());
  img.draw();
}
