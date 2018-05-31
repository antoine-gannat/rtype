#include "Animation.hpp"
#include "EntityEnemy.hpp"

EntityEnemy::EntityEnemy() : _anim(33, 36), img("./assets/textures/enemy.png")
{
  img.sprite.setScale({3, 3});
  for (int i = 0; i < 8/*nb frames*/ ; i++)
    {
      _anim.addFrame(i, sf::seconds(0.1));
    }
}

EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityEnemy::getPos() const
{
  return img.sprite.getPosition();
}

void EntityEnemy::update()
{
  img.sprite.setTextureRect(_anim.getFrame());
  img.draw();
  // CORE->window.draw(_animSprite);
}
