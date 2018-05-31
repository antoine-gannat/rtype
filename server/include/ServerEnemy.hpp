#pragma once

#include <chrono>
#include <math.h>
#include <ctime>
#include <iostream>
#include "AServerEntity.hpp"

class ServerEnemy : public AServerEntity
{
public:
	ServerEnemy();
	ServerEnemy(Position pos);
	virtual void move() = 0;
	bool shoot();

protected:
	Position _target;
	size_t _shootDelay;
	size_t _lastShoot;
};