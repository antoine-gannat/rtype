#include <ctime>
#include <iostream>
#include "Protocol.hpp"
#include "ServerPlayer.hpp"

Movements mvt[] =
{
	{Protocol::UP, &ServerPlayer::up},
	{Protocol::DOWN, &ServerPlayer::down},
	{Protocol::LEFT, &ServerPlayer::left},
	{Protocol::RIGHT, &ServerPlayer::right},
	{Protocol::UPRIGHT, &ServerPlayer::upRight},
	{Protocol::DOWNRIGHT, &ServerPlayer::downRight},
	{Protocol::UPLEFT, &ServerPlayer::upLeft},
	{Protocol::DOWNLEFT, &ServerPlayer::downLeft},
	{0, NULL}
};

ServerPlayer::ServerPlayer()
{
	_pos = Position(0, 0);
	_speed = 10;
	_type = Protocol::PLAYER;
	_height = 50;
	_width = 70;
	_bonus._timeActivated = -1;
}

ServerPlayer::ServerPlayer(ClientID id)
{
	_pos = Position(0, 0);
	_speed = 10;
	_type = Protocol::PLAYER;
	_clientId = id;
	_height = 50;
	_width = 70;
	_pos.x += _width / 2;
	_pos.y += _height / 2;
	_bonus._timeActivated = -1;
}

ServerPlayer::~ServerPlayer()
{
}

ClientID ServerPlayer::getClientID()
{
	return (_clientId);
}

void ServerPlayer::move(Protocol::PlayerUpdate data)
{
	if (_bonus._timeActivated > 0 && std::time(0) - _bonus._timeActivated > (int)bonusDuration)
	{
		std::cout << "Bonus on player " << _id << " stopped" << std::endl;
		_bonus._timeActivated = -1;
	}
	for (unsigned int i = 0; mvt[i].fct != NULL; i++)
	{
		if (mvt[i].key == data.key)
		{
			(this->*mvt[i].fct)();
			break;
		}
	}
}

void ServerPlayer::up()
{
	if ((_bonus._timeActivated < 0 || _bonus._bonusType != FAST) && _pos.y > _speed)
	{
		_pos.y -= _speed;
	}
	else if (_bonus._timeActivated > 0 && _bonus._bonusType == FAST && _pos.y > _speed * 2)
	{
		_pos.y -= _speed * 2;
	}
}

void ServerPlayer::down()
{
	if ((_bonus._timeActivated < 0 || _bonus._bonusType != FAST) && _pos.y + _speed < WINDOW_HEIGHT)
	{
		_pos.y += _speed;
	}
	else if (_bonus._timeActivated > 0 && _bonus._bonusType == FAST && _pos.y + _speed * 2 < WINDOW_HEIGHT)
	{
		_pos.y += _speed * 2;
	}
}

void ServerPlayer::left()
{
	if ((_bonus._timeActivated < 0 || _bonus._bonusType != FAST) && _pos.x > _speed)
	{
		_pos.x -= _speed;
	}
	else if (_bonus._timeActivated > 0 && _bonus._bonusType == FAST && _pos.x > _speed * 2)
	{
		_pos.x -= _speed * 2;
	}
}

void ServerPlayer::right()
{
	if ((_bonus._timeActivated < 0 || _bonus._bonusType != FAST) && _pos.x + _speed < WINDOW_WIDTH)
	{
		_pos.x += _speed;
	}
	else if (_bonus._timeActivated > 0 && _bonus._bonusType == FAST && _pos.x + _speed * 2  < WINDOW_WIDTH)
	{
		_pos.x += _speed * 2;
	}
}

void ServerPlayer::upRight()
{
	up();
	right();
}

void ServerPlayer::upLeft()
{
	up();
	left();
}

void ServerPlayer::downLeft()
{
	down();
	left();
}

void ServerPlayer::downRight()
{
	down();
	right();
}


void ServerPlayer::assignBonus(ServerBonus *bonus)
{
	_bonus._bonusType = TRIPLE_SHOOT;
	if (bonus)
		_bonus._bonusType = bonus->_bonusType;
	std::cout << "new bonus " << _bonus._bonusType << " added on player " << _id << std::endl; 
	_bonus._timeActivated = std::time(0);
}
