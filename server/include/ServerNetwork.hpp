#pragma once

#include <map>
#include <queue>
#include <thread>
#include <mutex>

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#endif

#include "IServerNetwork.hpp"
#include "BinaryBuff.hpp"

class ServerNetwork : public IServerNetwork
{
private:

  struct Client
  {
    Client() {}
    Client(const ClientID & _id) : id(_id) {}
    ClientID id;
    BinaryBuff inBuff;
    BinaryBuff outBuff;
  };

public:
  ServerNetwork(int port);
  ~ServerNetwork();

  bool readFromClient(void *data, size_t size, const ClientID & client);
  void writeToClient(const void *data, size_t size, const ClientID & client);
  bool getNewClient(ClientID & id);

private:
  void initUDP();
  void handleUDP();
  void handleUDPWrite();

private:
#if defined(_WIN32) || defined(WIN32)
  SOCKET _udpSocket;
#else
  int _udpSocket;
#endif
  unsigned short _port;
  std::map<ClientID, Client> _clients;
  std::queue<ClientID> _newClients;
  std::thread _udpThread;
  bool _run;
};

class ServerNetworkException: public std::runtime_error{
  public:
   ServerNetworkException():runtime_error("Network error"){}
   ServerNetworkException(std::string msg):runtime_error(msg.c_str()){}
 };

extern IServerNetwork* network;
