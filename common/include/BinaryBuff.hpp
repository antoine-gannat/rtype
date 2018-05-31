#pragma once

#include <queue>
#include <mutex>

class BinaryBuff : public std::queue<unsigned char>
{
public:
  void pushData(const unsigned char *data, size_t size);
  bool popData(unsigned char *data, size_t size);
  size_t flushData(unsigned char *data, size_t size);

private:
  std::mutex _lock;
};
