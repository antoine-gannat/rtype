#pragma once

#include <vector>
#include <string>

class AEntity;

class EntityManager
{
private:
  std::vector<AEntity*> _entities;
  std::vector<AEntity*> _to_delete;
  std::vector<AEntity*> _to_add;
public:
  EntityManager();
  virtual ~EntityManager();
  template<class T>
  T* addEntity(sf::Vector2f pos);
  AEntity *getById(int id);
  void update();
  void deleteEntity(AEntity*);
  void queueDeleteEntity(AEntity*);
  std::vector<AEntity*> getAll(std::string type);
  bool exists(AEntity* ent);
  void deleteZombieEntities();
};

template<class T>
T* EntityManager::addEntity(sf::Vector2f pos)
{
  T* ent;

  ent = new T();
  ent->init(this);
  ent->setPos(pos);
  _to_add.push_back(ent);
  return (ent);
}
