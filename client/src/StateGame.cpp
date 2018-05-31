#include <chrono>
#include <iostream>
#include "StateGame.hpp"
#include "EntityEnemy.hpp"
#include "EntityEnemy2.hpp"
#include "EntityShip.hpp"
#include "EntityFire.hpp"
#include "EntityEFire.hpp"
#include "EntityExplode.hpp"
#include "EntityStarfield.hpp"
#include "EntityBonus.hpp"
#include "StateMenu.hpp"
#include "StateOver.hpp"

keyMap map[] =
{
	{{sf::Keyboard::Left}, &StateGame::left, 1, Protocol::LEFT},
	{{sf::Keyboard::Right}, &StateGame::right, 1, Protocol::RIGHT},
	{{sf::Keyboard::Up}, &StateGame::up, 1, Protocol::UP},
	{{sf::Keyboard::Down}, &StateGame::down, 1, Protocol::DOWN},
	{{sf::Keyboard::Space}, &StateGame::space, 1, Protocol::SHOOT},
	{{sf::Keyboard::Left, sf::Keyboard::Down}, &StateGame::downLeft, 2, Protocol::DOWNLEFT},
	{{sf::Keyboard::Right, sf::Keyboard::Down}, &StateGame::downRight, 2, Protocol::DOWNRIGHT},
	{{sf::Keyboard::Left, sf::Keyboard::Up}, &StateGame::upLeft, 2, Protocol::UPLEFT},
	{{sf::Keyboard::Right, sf::Keyboard::Up}, &StateGame::upRight, 2, Protocol::UPRIGHT},
	{{sf::Keyboard::Unknown}, NULL, 1, Protocol::NONE}
};

StateGame::StateGame(std::string ip)
{
	network.setServerAddress(ip, 4242);
    if (!_soundBuffer.loadFromFile("./assets/shoot.ogg"))
    	throw std::runtime_error("cannot load sound file : ./assets/shoot.ogg");

}

StateGame::~StateGame()
{

}

void StateGame::begin()
{
	Protocol::PlayerUpdate start;

	start.key = Protocol::UP;
	network.writeToServer(&start, sizeof(start));
	_lastServerUpdate = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	manager.addEntity<EntityStarfield>({0, 0});
}

sf::Keyboard::Key StateGame::serverKeyToSFML(Protocol::PlayerKeys key)
{
	switch (key)
	{
 		case Protocol::UP:
 			return (sf::Keyboard::Up);
 		case Protocol::DOWN:
 			return (sf::Keyboard::Down);
 		case Protocol::LEFT:
 			return (sf::Keyboard::Left);
 		case Protocol::RIGHT:
 			return (sf::Keyboard::Right);
 		case Protocol::SHOOT:
 			return (sf::Keyboard::Space);
		default:
			return (sf::Keyboard::Unknown);
	}
	return (sf::Keyboard::Unknown);
}

IState* StateGame::update()
{
	std::vector<Protocol::EntityUpdate> allUpdates;
	Protocol::PlayerUpdate toSend;

	if (std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1) - _lastServerUpdate > TIMEOUT_CLIENT)
	{
		std::cout << "GAME OVER" << std::endl;
		return (new StateOver());
	}
	for (unsigned int i = 0; map[i].fct != NULL; i++)
	{
		if (map[i].nbKeyRequire == 1 && sf::Keyboard::isKeyPressed(map[i].key[0]))
		{
			(this->*map[i].fct)(toSend);
		}
		else if (map[i].nbKeyRequire == 2 && sf::Keyboard::isKeyPressed(map[i].key[0])
			&& sf::Keyboard::isKeyPressed(map[i].key[1]))
		{
			(this->*map[i].fct)(toSend);
		}
	}
	allUpdates = getUpdateFromServer();
	if (allUpdates.empty())
	{
		manager.update();
		return (nullptr);
	}
	_lastServerUpdate = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	applyUpdate(allUpdates);
	manager.update();
	return nullptr;
}

std::vector<Protocol::EntityUpdate> StateGame::getUpdateFromServer()
{
	Protocol::EntityUpdate buf;
	std::vector<Protocol::EntityUpdate> allData;

	while (network.readFromServer(&buf, sizeof(Protocol::EntityUpdate)))
	{
		bool found = false;
		for (unsigned int i = 0; i < allData.size(); i++)
		{
			if (allData[i].id == buf.id)
			{
				allData[i] = buf;
				found = true;
				break;
			}
		}
		if (!found)
			allData.push_back(buf);
	}
	return (allData);
}

void StateGame::applyUpdate(std::vector<Protocol::EntityUpdate> &data)
{
	AEntity *e;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		sf::Vector2f newpos(data[i].pos.x, data[i].pos.y);
		if ((e = manager.getById(data[i].id)) == nullptr && data[i].state != Protocol::DEAD)
		{
			if (data[i].type == Protocol::BULLET)
			{
				sound.setBuffer(_soundBuffer);
				sound.play();
				e = manager.addEntity<EntityFire>(newpos);
			}
			else if (data[i].type == Protocol::ENEMYBULLET)
			{
				e = manager.addEntity<EntityEFire>(newpos);
			}
			else if (data[i].type == Protocol::ENEMY)
				e = manager.addEntity<EntityEnemy>(newpos);
			else if (data[i].type == Protocol::ENEMY2)
				e = manager.addEntity<EntityEnemy2>(newpos);
			else if (data[i].type == Protocol::PLAYER)
				e = manager.addEntity<EntityShip>(newpos);
			else if (data[i].type == Protocol::BONUS)
				e = manager.addEntity<EntityBonus>(newpos);
			if (e != nullptr)
			{
				e->_id = data[i].id;
				e->lastUpdate = std::time(0);
				e->setPos(newpos);
			}
		}
		else if (e != nullptr && data[i].state == Protocol::DEAD)
		{
			e->kill();
			e = nullptr;
		}
		if (e != nullptr)
		{
			e->lastUpdate = std::time(0);
			e->setPos(newpos);			
		}
	}
	manager.deleteZombieEntities();
}

void StateGame::left(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::LEFT;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::right(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::RIGHT;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::up(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::UP;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::down(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::DOWN;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::space(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::SHOOT;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::downLeft(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::DOWNLEFT;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::downRight(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::DOWNRIGHT;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::upLeft(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::UPLEFT;
	network.writeToServer(&toSend, sizeof(toSend));
}

void StateGame::upRight(Protocol::PlayerUpdate &toSend)
{
	toSend.key = Protocol::UPRIGHT;
	network.writeToServer(&toSend, sizeof(toSend));
}
