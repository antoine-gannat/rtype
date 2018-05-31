#include <ctime>
#include "Core.hpp"
#include "AEntity.hpp"

AEntity::AEntity():
	_id(-1), lastUpdate(std::time(0))
{
}

void AEntity::init(EntityManager* manager)
{
  _manager = manager;
}

std::string AEntity::getType() const
{
  return ("entity");
}

void AEntity::kill()
{
  _manager->queueDeleteEntity(this);
}
