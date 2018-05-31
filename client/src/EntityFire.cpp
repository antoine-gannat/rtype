#include "EntityFire.hpp"
#include "EntityExplode.hpp"

EntityFire::EntityFire() :
  img("./assets/textures/fire.png")
{
  img.sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
  img.sprite.setScale({3, 3});
}

EntityFire::~EntityFire()
{
}

void EntityFire::setPos(sf::Vector2f pos)
{
  img.sprite.setPosition(pos);
}

sf::Vector2f EntityFire::getPos() const
{
  return img.sprite.getPosition();
}

void EntityFire::update()
{
  img.draw();
}

void EntityFire::kill()
{
  AEntity::kill();
  _manager->addEntity<EntityExplode>(this->getPos());
}
