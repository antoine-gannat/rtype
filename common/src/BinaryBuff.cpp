#include "BinaryBuff.hpp"

void BinaryBuff::pushData(const unsigned char *data, size_t size)
{
  _lock.lock();
  for (size_t i = 0; i < size; i++)
    this->push(data[i]);
  _lock.unlock();
}

bool BinaryBuff::popData(unsigned char *data, size_t size)
{
  _lock.lock();
  if (size > this->size())
  {
    _lock.unlock();
    return false;
  }
  for (size_t i = 0; i < size; i++)
  {
    data[i] = this->front();
    this->pop();
  }
  _lock.unlock();
  return true;
}

size_t BinaryBuff::flushData(unsigned char *data, size_t size)
{
  _lock.lock();
  size_t i;
  for (i = 0; i < size && !this->empty(); i++)
  {
    data[i] = this->front();
    this->pop();
  }
  _lock.unlock();
  return i;
}
