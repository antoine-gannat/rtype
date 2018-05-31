#include "Animation.hpp"
#include "EntityEFire.hpp"
#include "EntityExplode.hpp"

EntityEFire::EntityEFire() : _anim(7, 6), img("./assets/textures/enemy_fire.png")
{
  img.sprite.setScale({3, 3});
  for (int i = 0; i < 7/*nb frames*/ ; i++)
    {
      _anim.addFrame(i, sf::seconds(0.1));
    }
}

EntityEFire::~EntityEFire()
{
}

void EntityEFire::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityEFire::getPos() const
{
  return img.sprite.getPosition();
}

void EntityEFire::update()
{
  img.sprite.setTextureRect(_anim.getFrame());
  img.draw();
}

void EntityEFire::kill()
{
  AEntity::kill();
  _manager->addEntity<EntityExplode>(this->getPos());
}