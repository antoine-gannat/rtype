#pragma once

#include "Core.hpp"
#include "Image.hpp"

class StateOver : public IState
{
protected:
  Image background;
public:
  StateOver();
  virtual ~StateOver();
  void begin();
  IState* update();
};
