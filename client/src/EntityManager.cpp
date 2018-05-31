#include <sstream>
#include "Core.hpp"
#include "EntityManager.hpp"
#include "AEntity.hpp"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
  for (auto entity : _to_delete)
    {
      delete entity;
    }
  for (auto entity : _to_add)
    {
      delete entity;
    }
  for (auto entity : _entities)
    {
      delete entity;
    }
}

void EntityManager::update()
{
  for (auto entity : _entities)
    {
      entity->update();
    }
  for (auto entity : _to_delete)
    {
      deleteEntity(entity);
    }
  _entities.insert(_entities.end(), _to_add.begin(), _to_add.end());
  _to_add.clear();
  _to_delete.clear();
}

void EntityManager::deleteEntity(AEntity* entity)
{
  AEntity *ent;
  auto i = std::begin(_entities);

  while (i != std::end(_entities))
    {
      ent = *i;
      if (ent == entity)
        {
          i = _entities.erase(i);
          delete ent;
        }
      else
        ++i;
    }
}

void EntityManager::queueDeleteEntity(AEntity* entity)
{
  _to_delete.push_back(entity);
}

std::vector<AEntity*> EntityManager::getAll(std::string type)
{
  std::vector<AEntity*> res;
  std::stringstream type_str(type);
  std::string segment;
  std::vector<std::string> seglist;

  while(std::getline(type_str, segment, ':'))
    {
      seglist.push_back(segment);
    }
  for (auto entity : _entities)
    {
      for (auto seg : seglist)
        {
          if (entity->getType() == seg)
            res.push_back(entity);
        }
    }
  return (res);
}

bool EntityManager::exists(AEntity* entity)
{
  for (auto ent : _entities)
    {
      if (entity == ent)
        return (true);
    }
  return (false);
}

AEntity *EntityManager::getById(int id)
{
    for (auto ent : _entities)
    {
      if (ent->_id == id)
        return (ent);
    }
    return (nullptr);
}


void EntityManager::deleteZombieEntities()
{
    for (auto ent : _entities)
    {
      if (ent->_id != -2 && std::time(0) - ent->lastUpdate >= 10)
      {
        ent->kill();
      }
    }
}
