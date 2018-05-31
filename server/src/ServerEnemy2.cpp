#include "PatternLoader.hpp"
#include "ServerEnemy2.hpp"

ServerEnemy2::ServerEnemy2()
{
	_type = Protocol::ENEMY2;
	_hp = 100;
	_height = 70;
	_width = 50;
	_speed = 3;
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	_shootDelay = 1000;
}

ServerEnemy2::ServerEnemy2(Position pos)
{
	_type = Protocol::ENEMY2;
	setPos(pos);
	_hp = 100;
	_height = 70;
	_width = 50;
	_speed = 3;
	_target = pos;
	_lastShoot = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	_shootDelay = 1000;
}

void ServerEnemy2::move()
{
   	if (_state == Protocol::DEAD)
    {
    	return;
    }
	try {
		_pos = PatternLoader::getInst()->run("Sinus", _pos, _speed, &_target);
	} catch (PatternLoaderException &e) {
		std::cerr << e.what() << std::endl;
	}
}