#include <iostream>
#include "ServerEnemy.hpp"
#include "PatternLoader.hpp"

ServerEnemy::ServerEnemy()
{
	_type = Protocol::ENEMY;
	_hp = 100;
	_height = 70;
	_width = 50;
	_speed = 5;
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	_shootDelay = 1000;
}

ServerEnemy::ServerEnemy(Position pos)
{
	_type = Protocol::ENEMY;
	setPos(pos);
	_hp = 100;
	_height = 70;
	_width = 50;
	_pos.x += _width / 2;
	_pos.y += _height / 2;
	_speed = 5;
	_target = pos;
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	_shootDelay = 1000;
}

bool ServerEnemy::shoot()
{
	if (std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1) - _lastShoot < _shootDelay)
		return (false);
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	if (rand() % 2 == 0)
		return (false);
	return (true);
}
