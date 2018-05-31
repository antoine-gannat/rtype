#include <iostream>
#include <signal.h>
#include "ServerCore.hpp"
#include "ServerNetwork.hpp"

ServerCore::ServerCore()
{

}

ServerCore::~ServerCore()
{

}

void ServerCore::acceptNewPlayer()
{
  std::string newPlayerIp;
  ClientID tmp;

  if (network->getNewClient(tmp))
    _waitingPlayers.push_back(ServerPlayer(tmp));
  else
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void ServerCore::assignPlayersToGame()
{
  bool gameFound = false;

  std::cout << "Searching game to join ..." << std::endl;
  while (!_waitingPlayers.empty())
  {
    gameFound = false;
    std::cout << "games nb : "  << _games.size() << std::endl;
    for (unsigned int gameNb = 0; gameNb < _games.size(); gameNb++)
    {
      if (!_games[gameNb]->isFull())
      {
        std::cout << "Player : " << _waitingPlayers.front().getId() << " has join the Game " << gameNb << std::endl;
        _games[gameNb]->addNewPlayer(_waitingPlayers.front());
        _waitingPlayers.erase(_waitingPlayers.begin());
        gameFound = true;
        break;
      }
    }
    if (!gameFound)
    {
      if (_games.size() > 0)
        std::cout << "All games are full" << std::endl;
      ServerGame *newGame = new ServerGame;

      _gamesThreads.push_back(std::thread(&ServerGame::run, newGame));
      _games.push_back(newGame);
      std::cout << "Player : " << _waitingPlayers.front().getId() << " has join the Game " << _games.size() - 1 << std::endl;
      _games [_games.size() - 1]->addNewPlayer(_waitingPlayers.front());
      _waitingPlayers.erase(_waitingPlayers.begin());
    }
  }
}

void ServerCore::deleteFinishedGames()
{
  for (unsigned int i = 0; i < _games.size(); i++)
  {
    if (!_games[i]->isRunning())
    {
      delete _games[i];
      _games.erase(_games.begin() + i);
    }
  }
}

static bool stop = false;
static void sigHandler(int sig)
{
  if (sig == SIGINT)
    stop = true;
}

void ServerCore::run()
{
  signal(SIGINT, &sigHandler);
  while (!stop)
  {
      acceptNewPlayer();
      deleteFinishedGames();
      if (!_waitingPlayers.empty())
      {
        assignPlayersToGame();
      }
  }
  std::cout << "ServerCore done, waiting threads ..." << std::endl;
  for (unsigned int threadNb = 0; threadNb < _gamesThreads.size(); threadNb++)
  {
    if (threadNb < _games.size())
      _games[threadNb]->shutdown();
    _gamesThreads[threadNb].join();
  }
  for (unsigned int gameNb = 0; gameNb < _games.size(); gameNb++)
    delete _games[gameNb];
}
