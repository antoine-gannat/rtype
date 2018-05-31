#pragma once

#include <chrono>
#include "AServerEntity.hpp"
#include <math.h>
#include <ctime>

class ServerBullet : public AServerEntity
{
public:
	ServerBullet();
	ServerBullet(Position pos, size_t speed, bool friendly);
	bool updatePos();
	bool isFriendly();

private:
	bool _friendly; //true if shoot from a player
};
