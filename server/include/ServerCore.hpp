#pragma once

#include <vector>
#include <thread>
#include "ServerGame.hpp"

class ServerCore
{
public:
  ServerCore();
  ~ServerCore();
  void assignPlayersToGame();
  void acceptNewPlayer();
  void deleteFinishedGames();
  void run();

private:
  std::vector<ServerGame*> _games;
  std::vector<std::thread> _gamesThreads;
  std::vector<ServerPlayer> _waitingPlayers;
};
