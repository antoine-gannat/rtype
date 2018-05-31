#pragma once

#include "AServerEntity.hpp"
#include "Protocol.hpp"

static const size_t bonusDuration = 10; //10 sec

enum BonusTypes
{
	TRIPLE_SHOOT = 0,
	FAST,
	NONE
};

class ServerBonus : public AServerEntity
{
public:
	ServerBonus();
	ServerBonus(Position pos);
	void setType(BonusTypes type);
	ServerBonus *clone();
	BonusTypes _bonusType;
	int _timeActivated;
};