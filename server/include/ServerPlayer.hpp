#pragma once

#include "AServerEntity.hpp"
#include "IServerNetwork.hpp"
#include "ServerBonus.hpp"

class ServerPlayer;

struct Movements
{
	int key;
	void (ServerPlayer::*fct)();
};

class ServerPlayer : public AServerEntity
{
public:
	ServerPlayer();
	ServerPlayer(ClientID id);
	~ServerPlayer();
	ClientID getClientID();
	void assignBonus(ServerBonus *bonus);
	void move(Protocol::PlayerUpdate data);
	void up();
	void down();
	void left();
	void right();
	void upRight();
	void upLeft();
	void downLeft();
	void downRight();

	ServerBonus _bonus;
private:
	ClientID _clientId;
};