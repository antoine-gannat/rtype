#include "ServerBonus.hpp"

ServerBonus::ServerBonus()
{
	_type = Protocol::BONUS;
	_height = 200;
	_width = 200;
	_timeActivated = 0;
	_bonusType = NONE;
}

ServerBonus::ServerBonus(Position pos)
{
	_timeActivated = 0;
	_pos = pos;
	setType((BonusTypes)(rand() % 2));
	_type = Protocol::BONUS;
	_height = 200;
	_width = 200;
}

void ServerBonus::setType(BonusTypes type)
{
	_bonusType = type;
}

ServerBonus *ServerBonus::clone()
{
	ServerBonus *dest = new ServerBonus();

	dest->_type = this->_type;
	dest->_state = this->_state;
	dest->_id = this->_id;
	dest->_nbFrameDead = this->_nbFrameDead;
	dest->_speed = this->_speed;
	dest->_height = this->_height;
	dest->_width = this->_width;
	dest->_bonusType = this->_bonusType;
	return (dest);
}