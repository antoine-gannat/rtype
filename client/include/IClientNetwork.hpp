#pragma once

#include <string>

class IClientNetwork
{
public:
  virtual ~IClientNetwork() {}

  virtual void setServerAddress(const std::string & ip, int port) = 0; // shall be set before any read or write

  virtual bool readFromServer(void *data, size_t size) = 0; // return true if 'data' has been filled
  virtual void writeToServer(const void *data, size_t size) = 0;
};
