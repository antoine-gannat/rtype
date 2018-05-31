#pragma once

#include "Core.hpp"
#include "AEntity.hpp"
#include "EntityManager.hpp"
#include "Image.hpp"
#include "Animation.hpp"

class EntityEnemy : public AEntity
{
protected:
  Animation _anim;
  sf::RectangleShape _animSprite;
  sf::Texture _texture;
  Image img;

public:
  EntityEnemy();
  virtual ~EntityEnemy();
  void setPos(sf::Vector2f pos);
  sf::Vector2f getPos() const;
  void update();
};
