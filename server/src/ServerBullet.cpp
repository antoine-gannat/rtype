#include <iostream>
#include "ServerBullet.hpp"

ServerBullet::ServerBullet()
{
	_friendly = false;
}

ServerBullet::ServerBullet(Position pos, size_t speed, bool friendly = false)
{
	_damage = 10;
	_pos = pos;
	if (friendly == false)
	{
		_type = Protocol::ENEMYBULLET;
	}
	else
	{
		_type = Protocol::BULLET;
	}
	_speed = speed;
	_friendly = friendly;
}

//return false if bullet goes out of the window
bool ServerBullet::updatePos()
{
	if (_friendly)
	{
		_pos.x += _speed;
		if (_pos.x >= WINDOW_WIDTH)
			return (false);
	}
	else
	{
		_pos.x -= _speed;
		if (_pos.x < 0)
			return (false);		
	}
	return (true);
}

bool ServerBullet::isFriendly()
{
	return (_friendly);
}
