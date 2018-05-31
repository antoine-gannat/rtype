#pragma once

#include <string>
#include "Protocol.hpp"

class ServerBonus;

class IServerEntity
{
public:
	virtual ~IServerEntity() {}
	virtual Position getPos() = 0;
	virtual Protocol::EntityType getType() = 0;
	virtual Protocol::EntityState getState() = 0;
	virtual void setState(Protocol::EntityState) = 0;
	virtual void setType(Protocol::EntityType t) = 0;
	virtual Protocol::UID getId() = 0;
	virtual bool takeDamage(int dmg) = 0;
	virtual bool giveDamage(IServerEntity *to) = 0;
	virtual size_t getNbFrameDead() = 0;
	virtual size_t getHeight() = 0;
	virtual size_t getWidth() = 0;
	virtual void setNbFrameDead(size_t nb) = 0;
};

