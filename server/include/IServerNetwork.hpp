#pragma once

#include <string>

struct ClientID
{
  ClientID() {}
  ClientID(unsigned int _ip, unsigned short _port) : ip(_ip), port(_port) {}

  unsigned int ip;
  unsigned short port;

  bool operator<(const ClientID & other) const { return (port ^ ip) < (other.port ^ other.ip); }
};

class IServerNetwork
{
public:
  virtual ~IServerNetwork() {}

  virtual bool readFromClient(void *data, size_t size, const ClientID & id) = 0; // return true if 'data' has been filled
  virtual void writeToClient(const void *data, size_t size, const ClientID & id) = 0;
  virtual bool getNewClient(ClientID & id) = 0; // return true if 'id' has been filled
};
