#pragma once

#include "IServerEntity.hpp"

#define HIT_RADIUS 30
#define NB_FRAME_DEAD_BEFORE_DELETE 3

class AServerEntity : public IServerEntity
{
public:
	AServerEntity();
	~AServerEntity();

	Position getPos();
	void setPos(Position pos);
	Protocol::EntityType getType();
	void setType(Protocol::EntityType t);
	Protocol::EntityState getState();
	void setState(Protocol::EntityState);
	Protocol::UID getId();
	bool takeDamage(int val); //return true if the entity died
	bool giveDamage(IServerEntity *to); //return true if "to" died
	size_t getDamage();
	size_t getNbFrameDead();
	size_t getHeight();
	size_t getWidth();
	void setNbFrameDead(size_t nb);
	IServerEntity *clone();

protected:
	int _hp;
	std::string _name;
	Position _pos;
	Protocol::EntityType _type;
	Protocol::EntityState _state;
	Protocol::UID _id;
	static Protocol::UID idIndex;
	size_t _damage;
	size_t _nbFrameDead; //used to send DEAD status to client, then the entity is deleted after NB_FRAME_DEAD_BEFORE_DELETE of dead frame
	int _speed;
	size_t _height; //used for colision
	size_t _width; //used for colision
	//powerups
};