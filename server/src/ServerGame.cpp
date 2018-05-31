#include <iostream>
#include <math.h>
#include <ctime>
#include "ServerGame.hpp"
#include "ServerBullet.hpp"
#include "ServerNetwork.hpp"
#include "ServerEnemy.hpp"
#include "ServerEnemy1.hpp"
#include "ServerEnemy2.hpp"
#include "ServerBonus.hpp"

unsigned short ServerGame::idIndex = 0;

ServerGame::ServerGame()
{
	_running = true;
	_id = idIndex;
	idIndex++;
	_waveNb = 0;
	std::cout << "Game " << _id << " created" << std::endl;
}

ServerGame::~ServerGame()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		delete _entities[i];
	}
}

void ServerGame::shutdown()
{
	_running = false;
}

size_t ServerGame::getNbPlayer()
{
	size_t res;

	_playersMut.lock();
	res = _players.size();
	_playersMut.unlock();
	return (res);
}

bool ServerGame::isFull()
{
	if (getNbPlayer() >= MAX_USER_PER_GAME)
		return (true);
	return (false);
}

void ServerGame::addNewPlayer(ServerPlayer p)
{
	_playersMut.lock();
	_players.push_back(p);
	_playersMut.unlock();
}

void ServerGame::sendAllPos()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		Protocol::EntityUpdate toSend;

		if (_entities[i]->getState() == Protocol::DEAD)
		{
			_entities[i]->setNbFrameDead(_entities[i]->getNbFrameDead() + 1);
			if (_entities[i]->getNbFrameDead() > NB_FRAME_DEAD_BEFORE_DELETE)
			{
				delete _entities[i];
				_entities.erase(_entities.begin() + i);
				continue;
			}
		}
		toSend.id = _entities[i]->getId();
		toSend.type = _entities[i]->getType();
		toSend.pos = _entities[i]->getPos();
		toSend.state = _entities[i]->getState();
		for (unsigned int j = 0; j < _players.size(); j++)
			network->writeToClient(&toSend, sizeof(Protocol::EntityUpdate), _players[j].getClientID());
	}
	for (unsigned int i = 0; i < _players.size(); i++)
	{
		Protocol::EntityUpdate toSend;

		if (_players[i].getState() == Protocol::DEAD)
		{
			_players[i].setNbFrameDead(_players[i].getNbFrameDead() + 1);
			if (_players[i].getNbFrameDead() > NB_FRAME_DEAD_BEFORE_DELETE)
			{
				std::cout << "Player " <<  _players[i].getId() << " is dead";
				_players.erase(_players.begin() + i);
				continue;
			}
		}
		toSend.id = _players[i].getId();
		toSend.type = _players[i].getType();
		toSend.pos = _players[i].getPos();
		toSend.state = _players[i].getState();
		for (unsigned int i = 0; i < _players.size(); i++)
		{
			network->writeToClient(&toSend, sizeof(Protocol::EntityUpdate), _players[i].getClientID());
		}
	}
}

void ServerGame::readPosFromClient()
{
	for (unsigned int i = 0; i < getNbPlayer(); i++)
	{
		Protocol::PlayerUpdate buf;

		_playersMut.lock();
		std::vector<Protocol::PlayerUpdate> allData;

		while (network->readFromClient(&buf, sizeof(Protocol::PlayerUpdate), _players[i].getClientID()))
		{
			allData.push_back(buf);
		}
		for (unsigned int j = 0; j < allData.size(); j++)
		{
			if (allData[j].key == Protocol::SHOOT)
			{
				_entities.push_back(new ServerBullet(_players[i].getPos(), 50, true));
				if (_players[i]._bonus._timeActivated > 0 && _players[i]._bonus._bonusType == TRIPLE_SHOOT)
				{
					_entities.push_back(new ServerBullet(Position(_players[i].getPos().x, _players[i].getPos().y + 10), 50, true));
					_entities.push_back(new ServerBullet(Position(_players[i].getPos().x, _players[i].getPos().y - 10), 50, true));
				}
			}
			else
				_players[i].move(allData[j]);
		}
		_playersMut.unlock();
	}
}

void ServerGame::moveEnemy()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getType() == Protocol::ENEMY || _entities[i]->getType() == Protocol::ENEMY2)
		{
			((ServerEnemy*)_entities[i])->move();
			if (((ServerEnemy*)_entities[i])->shoot())
			{
				Position shootPos = _entities[i]->getPos();
				shootPos.y += _entities[i]->getHeight() / 2;
				shootPos.x += _entities[i]->getWidth() / 2;
				_entities.push_back(new ServerBullet(shootPos, 10, false));
			}
		}
	}
}

void ServerGame::run()
{
	bool hasStarted = false;

	while (_running)
	{
		if (hasStarted && _players.size() == 0)
		{
			std::cout << "Game " << _id << " is over: everyone is dead" << std::endl;
			_running = false;
			return;
		}
		if (_players.size() > 0)
			hasStarted = true;
		checkBonus();
		sendAllPos();
		readPosFromClient();
		updateBullets();
		moveEnemy();
		if (waveFinished())
			addNewWave();
		frameLimit();
	}
	std::cout << "Game " << _id << " done" << std::endl;
}

bool ServerGame::hasHit(IServerEntity *entity1, IServerEntity *entity2)
{
	Position entity1Pos = entity1->getPos();
	Position entity2Pos = entity2->getPos();

	if (entity1Pos.x >= entity2Pos.x && entity1Pos.x <= entity2Pos.x + (int)entity2->getWidth()
		&& entity1Pos.y >= entity2Pos.y && entity1Pos.y <= entity2Pos.y + (int)entity2->getHeight())
		return (true);
	return (false);
}

bool ServerGame::checkBulletHit(ServerBullet *entityToCheck)
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getId() != entityToCheck->getId()
			&& entityToCheck->isFriendly()
			&& (_entities[i]->getType() == Protocol::ENEMY || _entities[i]->getType() == Protocol::ENEMY2)
			&& hasHit(entityToCheck, _entities[i]))
		{
			if (entityToCheck->giveDamage(_entities[i]) && rand() % 30 == 0) //chance of bonus drop
			{
				_entities.push_back(new ServerBonus(_entities[i]->getPos()));
				std::cout << "Bonus spawned @ " << _entities[i]->getPos().x << " " << _entities[i]->getPos().y << std::endl;
			}

			return (true);
		}
	}
	for (unsigned int i = 0; i < _players.size(); i++)
	{
		if (!entityToCheck->isFriendly()
			&& hasHit(entityToCheck, &_players[i]))
		{
			entityToCheck->giveDamage(&_players[i]);
			return (true);
		}
	}
	return (false);
}

void ServerGame::updateBullets()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getType() == Protocol::BULLET || _entities[i]->getType() == Protocol::ENEMYBULLET)
		{
			if (!((ServerBullet*)_entities[i])->updatePos() || checkBulletHit((ServerBullet*)_entities[i]))
			{
				((ServerBullet*)_entities[i])->setState(Protocol::DEAD);
			}
		}
	}
}

const ServerGame::Milliseconds ServerGame::_frameDuration =
static_cast<ServerGame::Milliseconds>(1000 / 50);

void ServerGame::frameLimit()
{
  static Clock::time_point t0 = Clock::now();
  Clock::time_point t1;
  Milliseconds actDuration;
  t1 = Clock::now();
  actDuration = std::chrono::duration_cast<Milliseconds>(t1 - t0);
  if (actDuration < _frameDuration)
    std::this_thread::sleep_for(_frameDuration - actDuration);
  t0 = Clock::now();
}

bool ServerGame::waveFinished()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getType() == Protocol::ENEMY || _entities[i]->getType() == Protocol::ENEMY2)
			return (false);
	}
	return (true);
}

void ServerGame::addNewWave()
{
	_waveNb++;
	for (unsigned int nbSpawn = 0; nbSpawn < 3 * (_waveNb * 0.5); nbSpawn++)
	{
		if (rand() % 3 == 0)
		{
			_entities.push_back(new ServerEnemy2(Position(WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
		}
		else
		{
			_entities.push_back(new ServerEnemy1(Position(WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
		}
	}
}

bool ServerGame::isRunning()
{
	return (_running);
}

void ServerGame::checkBonus()
{
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->getType() == Protocol::BONUS  && _entities[i]->getState() != Protocol::DEAD)
		{
			for (unsigned int j = 0; j < _players.size(); j++)
			{
				if (hasHit(&_players[j], _entities[i]))
				{
					_players[j].assignBonus((ServerBonus*)_entities[i]);
					_entities[i]->setState(Protocol::DEAD);
				}
			}
		}
	}
}
