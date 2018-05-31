#pragma once

#include "Core.hpp"
#include "AEntity.hpp"
#include "EntityManager.hpp"
#include "Image.hpp"

class EntityStarfield : public AEntity
{
protected:
  Image img;

public:
  EntityStarfield();
  virtual ~EntityStarfield();
  void setPos(sf::Vector2f pos);
  sf::Vector2f getPos() const;
  void update();

private:
  int _scrollState;
};
