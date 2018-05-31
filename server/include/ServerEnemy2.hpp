#pragma once

#include <chrono>
#include <math.h>
#include <ctime>
#include "AServerEntity.hpp"
#include "ServerEnemy.hpp"

class ServerEnemy2 : public ServerEnemy
{
public:
	ServerEnemy2();
	ServerEnemy2(Position pos);
	void move();
};