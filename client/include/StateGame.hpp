#pragma once

#include <SFML/Audio.hpp>
#include "Core.hpp"
#include "Image.hpp"
#include "Protocol.hpp"

static const int TIMEOUT_CLIENT = 1000; //1 sec

class StateGame;

struct keyMap
{
	sf::Keyboard::Key key[5];
	void (StateGame::*fct)(Protocol::PlayerUpdate &toSend);
  short nbKeyRequire;
  Protocol::PlayerKeys keyServ;
};

class StateGame : public IState
{
protected:
  EntityManager manager;
  ClientNetwork network;
  size_t _lastServerUpdate;
  sf::SoundBuffer _soundBuffer;
  sf::Sound sound;

public:
  StateGame(std::string ip);
  virtual ~StateGame();
  void begin();
  IState* update();
  sf::Keyboard::Key serverKeyToSFML(Protocol::PlayerKeys key);
  std::vector<Protocol::EntityUpdate> getUpdateFromServer();
  void applyUpdate(std::vector<Protocol::EntityUpdate> &data);
  void left(Protocol::PlayerUpdate &toSend);
  void right(Protocol::PlayerUpdate &toSend);
  void up(Protocol::PlayerUpdate &toSend);
  void down(Protocol::PlayerUpdate &toSend);
  void space(Protocol::PlayerUpdate &toSend);
  void downLeft(Protocol::PlayerUpdate &toSend);
  void downRight(Protocol::PlayerUpdate &toSend);
  void upLeft(Protocol::PlayerUpdate &toSend);
  void upRight(Protocol::PlayerUpdate &toSend);
};
