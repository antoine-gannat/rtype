#include "Animation.hpp"
#include "EntityExplode.hpp"

EntityExplode::EntityExplode() : _anim(32, 32), img("./assets/textures/explosion.png")
{
  img.sprite.setScale({3, 3});
  for (int i = 0; i < 6 ; i++)
    {
      _anim.addFrame(i, sf::seconds(0.1));
    }
}

EntityExplode::~EntityExplode()
{
}

void EntityExplode::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityExplode::getPos() const
{
  return img.sprite.getPosition();
}

void EntityExplode::update()
{
  img.sprite.setTextureRect(_anim.getFrame());
  img.draw();
  if (clock.getElapsedTime().asMilliseconds() >= 550)
    this->kill();
}
