#pragma once

#include "Core.hpp"
#include "AEntity.hpp"
#include "EntityManager.hpp"
#include "Image.hpp"

class EntityFire : public AEntity
{
protected:
  Image img;

public:
  EntityFire();
  virtual ~EntityFire();
  void setPos(sf::Vector2f pos);
  sf::Vector2f getPos() const;
  void update();
  void kill();
};
