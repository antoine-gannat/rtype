#pragma once

#include <chrono>
#include <math.h>
#include <ctime>
#include "AServerEntity.hpp"
#include "ServerEnemy.hpp"

class ServerEnemy1 : public ServerEnemy
{
public:
	ServerEnemy1();
	ServerEnemy1(Position pos);
	void move();
};