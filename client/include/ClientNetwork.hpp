#pragma once

#include <stdexcept>
#include <thread>

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <arpa/inet.h>
#endif

#include "IClientNetwork.hpp"
#include "BinaryBuff.hpp"

class ClientNetwork : public IClientNetwork
{
public:
  ClientNetwork();
  ClientNetwork(const std::string & ip, int port);
  ~ClientNetwork();

  void setServerAddress(const std::string & ip, int port);

  bool readFromServer(void *data, size_t size);
  void writeToServer(const void *data, size_t size);

private:
  void initSocket();
  void handleUDP();
  void handleUDPWrite();

private:
  std::string _ip;
  unsigned short _port;
#if defined(_WIN32) || defined(WIN32)
  SOCKET _socket;
#else
  int _socket;
#endif
  std::thread _udpThread;
  bool _run;
  BinaryBuff _inBuff;
  BinaryBuff _outBuff;
  struct sockaddr_in _si;
};

class ClientNetworkException : public std::runtime_error {
  public:
   ClientNetworkException() : runtime_error("Network error") {}
   ClientNetworkException(std::string msg) : runtime_error(msg.c_str()) {}
 };

extern IClientNetwork* network;
