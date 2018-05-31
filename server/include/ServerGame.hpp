#pragma once

#include <vector>
#include <atomic>
#include <mutex>
#include <chrono>
#include "IServerEntity.hpp"
#include "ServerPlayer.hpp"
#include "ServerBullet.hpp"
#include "Protocol.hpp"

#define MAX_USER_PER_GAME 4

class ServerGame
{
public:
	ServerGame();
	~ServerGame();

	bool isFull();
	size_t getNbPlayer();
	void addNewPlayer(ServerPlayer p);
	void run();
	void shutdown();
  	void sendAllPos();
	void readPosFromClient();
	void updateBullets();
	void moveEnemy();
	bool hasHit(IServerEntity *enitity1, IServerEntity *enitity2);
	bool checkBulletHit(ServerBullet *enitityToCheck);
	bool waveFinished();
	void addNewWave();
	bool isRunning();
	void checkBonus();

private:
	std::vector<IServerEntity*> _entities;
	std::vector<ServerPlayer> _players;
	std::mutex _playersMut;
	std::atomic<bool> _running;
	Protocol::UID _id;
	static unsigned short idIndex;
	size_t _waveNb;

private: // Frame handling
	typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::milliseconds Milliseconds;
  void frameLimit();
	static const Milliseconds _frameDuration;
};
