#pragma once

#include "Core.hpp"
#include "AEntity.hpp"
#include "EntityManager.hpp"
#include "Image.hpp"

class EntityShip : public AEntity
{
protected:
  Image *img;
  bool nokey;
  static int index;
  int _id;

public:
  EntityShip();
  virtual ~EntityShip();
  void setPos(sf::Vector2f pos);
  sf::Vector2f getPos() const;
  void update();
};
