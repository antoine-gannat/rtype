#include "Animation.hpp"
#include "EntityEnemy2.hpp"

EntityEnemy2::EntityEnemy2() : _anim(62, 46), img("./assets/textures/enemy2.png")
{
  img.sprite.setScale({3, 3});
  for (int i = 0; i < 6/*nb frames*/ ; i++)
    {
      _anim.addFrame(i, sf::seconds(0.1));
    }
}

EntityEnemy2::~EntityEnemy2()
{
}

void EntityEnemy2::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityEnemy2::getPos() const
{
  return img.sprite.getPosition();
}

void EntityEnemy2::update()
{
  img.sprite.setTextureRect(_anim.getFrame());
  img.draw();
  // CORE->window.draw(_animSprite);
}
