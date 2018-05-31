#include "PatternLoader.hpp"
#include "ServerEnemy1.hpp"

ServerEnemy1::ServerEnemy1()
{
	_type = Protocol::ENEMY;
	_hp = 100;
	_height = 70;
	_width = 50;
	_speed = 5;
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	_shootDelay = 1000;
}

ServerEnemy1::ServerEnemy1(Position pos)
{
	_type = Protocol::ENEMY;
	setPos(pos);
	_hp = 100;
	_height = 70;
	_width = 50;
	_speed = 5;
	_target = pos;
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	_shootDelay = 1000;
}

void ServerEnemy1::move()
{
   	if (_state == Protocol::DEAD)
    {
    	return;
    }
	try {
		_pos = PatternLoader::getInst()->run("Focus", _pos, _speed, &_target);
	} catch (PatternLoaderException &e) {
		std::cerr << e.what() << std::endl;
	}
}