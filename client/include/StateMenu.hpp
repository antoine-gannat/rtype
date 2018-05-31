#pragma once

#include "Core.hpp"
#include "Image.hpp"

class StateMenu : public IState
{
protected:
  Image background;
  Text ip_hint;
  Text ip;
  Text _gameName;
public:
  StateMenu();
  virtual ~StateMenu();
  void begin();
  IState* update();
};
