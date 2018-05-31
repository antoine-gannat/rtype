#include <iostream>
#include <string.h>
#if defined(_WIN32) || defined(WIN32)
#include <Ws2tcpip.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#endif
#include "ServerNetwork.hpp"

ServerNetwork::ServerNetwork(int port) : _port(port), _run(true)
{
  initUDP();
  _udpThread = std::thread(&ServerNetwork::handleUDP, this);
}

ServerNetwork::~ServerNetwork()
{
#if defined(_WIN32) || defined(WIN32)
  closesocket(_udpSocket);
#else
  close(_udpSocket);
#endif
  _run = false;
  _udpThread.join();
}

void ServerNetwork::handleUDP()
{
  struct pollfd pollStruct;
  pollStruct.fd = _udpSocket;
  pollStruct.events = POLLIN;
  while (_run)
  {
    handleUDPWrite();
#if defined(_WIN32) || defined(WIN32)
    if (WSAPoll(&pollStruct, 1, 50) != 1)
      continue;
#else
    if (poll(&pollStruct, 1, 50) != 1)
      continue;
#endif
    if (pollStruct.revents & POLLIN)
    {
      unsigned char buff[512];
      struct sockaddr_in si_other;
      int len = sizeof(struct sockaddr_in);
#if defined(_WIN32) || defined(WIN32)
      int ret = recvfrom(_udpSocket, (char*)buff, 512, 0, (struct sockaddr*)&si_other, &len);
#else
      int ret = recvfrom(_udpSocket, buff, 512, 0, (struct sockaddr*)&si_other, (socklen_t*)&len);
#endif
      if (ret <= 0)
        continue;
      ClientID id(si_other.sin_addr.s_addr, si_other.sin_port);
      if (_clients.find(id) == _clients.end())
      {
        _clients.emplace(id, id);
        _newClients.push(id);
      }
      _clients[id].outBuff.pushData(buff, ret);
    }
  }
}

void ServerNetwork::handleUDPWrite()
{
  for (auto & c : _clients)
  {
    if (c.second.inBuff.empty())
      continue;
    unsigned char buff[4096];
    struct sockaddr_in si_other;
    int len = sizeof(struct sockaddr_in);

    memset((char*)&si_other, 0, len);
    si_other.sin_family = AF_INET;
    si_other.sin_port = c.second.id.port;
    si_other.sin_addr.s_addr = c.second.id.ip;

    size_t ret = c.second.inBuff.flushData(buff, 4096);
#if defined(_WIN32) || defined(WIN32)
    sendto(_udpSocket, (char*)buff, (int)ret, 0, (const struct sockaddr*)&si_other, len);
#else
    sendto(_udpSocket, buff, ret, 0, (const struct sockaddr*)&si_other, (socklen_t)len);
#endif
  }
}

void ServerNetwork::initUDP()
{
  struct sockaddr_in si_serv;
  int slen = sizeof(struct sockaddr_in);

#if defined(_WIN32) || defined(WIN32)
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
  if ((_udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    throw ServerNetworkException("UDP socket() failed");

  memset((char*)&si_serv, 0, slen);
  si_serv.sin_family = AF_INET;
  si_serv.sin_port = htons(_port);
  si_serv.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(_udpSocket, (struct sockaddr*)&si_serv, slen) == -1)
    throw ServerNetworkException("UDP bind() failed");
}

bool ServerNetwork::readFromClient(void *data, size_t size, const ClientID & id)
{
  if (_clients.find(id) == _clients.end())
    return false;
  return _clients[id].outBuff.popData(static_cast<unsigned char*>(data), size);
}

void ServerNetwork::writeToClient(const void *data, size_t size, const ClientID & id)
{
  if (_clients.find(id) == _clients.end())
    return;
  _clients[id].inBuff.pushData(static_cast<const unsigned char*>(data), size);
}

bool ServerNetwork::getNewClient(ClientID & id)
{
  if (_newClients.empty())
    return false;
  id = _newClients.front();
  _newClients.pop();
  return true;
}
