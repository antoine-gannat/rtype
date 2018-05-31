#include "AServerEntity.hpp"
#include "ServerBonus.hpp"

Protocol::UID AServerEntity::idIndex = 1;

AServerEntity::AServerEntity()
{
	_state = Protocol::IDLE;
	_id = idIndex;
	idIndex++;
	_hp = 0;
	_nbFrameDead = 0;
	_height = 0;
	_width = 0;
	_speed = 0;
}

AServerEntity::~AServerEntity()
{
}

Position AServerEntity::getPos()
{
	return (_pos);
}

Protocol::EntityState AServerEntity::getState()
{
	return (_state);
}

Protocol::EntityType AServerEntity::getType()
{
	return (_type);
}

Protocol::UID AServerEntity::getId()
{
	return (_id);
}

bool AServerEntity::takeDamage(int val)
{
	_hp -= val;
	if (_hp <= 0)
	{
		_state = Protocol::DEAD;
		return (true);
	}
	return (false);
}

bool AServerEntity::giveDamage(IServerEntity *to)
{
	return (to->takeDamage(_damage));
}

size_t AServerEntity::getDamage()
{
	return (_damage);
}

size_t AServerEntity::getNbFrameDead()
{
	return (_nbFrameDead);
}

void AServerEntity::setNbFrameDead(size_t nb)
{
	_nbFrameDead = nb;
}

void AServerEntity::setPos(Position pos)
{
	_pos = pos;
}

void AServerEntity::setState(Protocol::EntityState state)
{
	_state = state;
}

size_t AServerEntity::getHeight()
{
	return (_height);
}

size_t AServerEntity::getWidth()
{
	return (_width);
}


void AServerEntity::setType(Protocol::EntityType t)
{
	_type = t;
}
