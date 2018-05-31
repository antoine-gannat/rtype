#pragma once

class IState
{
public:
  virtual ~IState() {};
  virtual void begin() = 0;
  virtual IState* update() = 0;
};
