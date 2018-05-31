#if defined(_WIN32) || defined(WIN32)
#include <Ws2tcpip.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#endif

#include <cstring>
#include "ClientNetwork.hpp"

ClientNetwork::ClientNetwork() : _run(true)
{
  initSocket();
}

ClientNetwork::ClientNetwork(const std::string & ip, int port) : _run(true)
{
  setServerAddress(ip, port);
  initSocket();
}

ClientNetwork::~ClientNetwork()
{
  #if defined(_WIN32) || defined(WIN32)
  closesocket(_socket);
  #else
  close(_socket);
  #endif
  _run = false;
  _udpThread.join();
}

void ClientNetwork::initSocket()
{
#if defined(_WIN32) || defined(WIN32)
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
  if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    throw ClientNetworkException("UDP socket() failed");
  _udpThread = std::thread(&ClientNetwork::handleUDP, this);
}

void ClientNetwork::handleUDP()
{
  struct pollfd pollStruct;
  pollStruct.fd = _socket;
  pollStruct.events = POLLIN;
  while (_run)
  {
    if (!_outBuff.empty())
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
      unsigned char buff[4096];
      struct sockaddr_in si_other;
      int len = sizeof(struct sockaddr_in);
#if defined(_WIN32) || defined(WIN32)
      int ret = recvfrom(_socket, (char*)buff, 4096, 0, (struct sockaddr*)&si_other, &len);
#else
      int ret = recvfrom(_socket, buff, 4096, 0, (struct sockaddr*)&si_other, (socklen_t*)&len);
#endif
      if (ret <= 0)
        continue;
      _inBuff.pushData(buff, ret);
    }
  }
}

void ClientNetwork::handleUDPWrite()
{
    unsigned char buff[512];
    size_t ret = _outBuff.flushData(buff, 512);

#if defined(_WIN32) || defined(WIN32)
    sendto(_socket, (char*)buff, (int)ret, 0, (const struct sockaddr*)&_si, sizeof(_si));
#else
    sendto(_socket, buff, ret, 0, (const struct sockaddr*)&_si, (socklen_t)sizeof(_si));
#endif
}

void ClientNetwork::setServerAddress(const std::string & ip, int port)
{
  _ip = ip;
  _port = port;
  memset((char*)&_si, 0, sizeof(struct sockaddr_in));
  _si.sin_family = AF_INET;
  _si.sin_port = htons(_port);
  if (inet_pton(AF_INET, _ip.c_str(), &_si.sin_addr) == 0)
	  throw ClientNetworkException("UDP inet_aton() failed");
}

bool ClientNetwork::readFromServer(void *data, size_t size)
{
  return _inBuff.popData(static_cast<unsigned char*>(data), size);
}

void ClientNetwork::writeToServer(const void *data, size_t size)
{
  _outBuff.pushData(static_cast<const unsigned char*>(data), size);
}
