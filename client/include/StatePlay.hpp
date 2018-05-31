#pragma once

#include "Core.hpp"
#include "Animation.hpp"

class StatePlay : public IState
{
protected:
  Animation _anim;
  sf::RectangleShape _animSprite;
  sf::Texture _texture;
  
public:
  StatePlay();
  virtual ~StatePlay();
  void begin();
  IState* update();
};
