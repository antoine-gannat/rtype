#pragma once

#include "Core.hpp"
#include "EntityManager.hpp"

class AEntity
{
protected:
  EntityManager* _manager;
public:
  AEntity();
  virtual ~AEntity() {};

  virtual void init(EntityManager* manager);
  virtual void setPos(sf::Vector2f pos) = 0;
  virtual sf::Vector2f getPos() const = 0;
  virtual void update() = 0;
  virtual std::string getType() const;
  virtual void kill();

  int _id;
  size_t lastUpdate;
};

