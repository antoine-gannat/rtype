#pragma once

#include "Core.hpp"
#include "Image.hpp"

class StateSplash : public IState
{
protected:
  Image background;
  sf::Clock clock;
public:
  StateSplash();
  virtual ~StateSplash();
  void begin();
  IState* update();
};
