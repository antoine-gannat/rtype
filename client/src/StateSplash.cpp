#include "Animation.hpp"
#include "StateSplash.hpp"
#include "StateMenu.hpp"

StateSplash::StateSplash() :
  background("assets/splashscreen.png", 1)
{
  
}

StateSplash::~StateSplash()
{

}

void StateSplash::begin()
{
}

IState* StateSplash::update()
{
  if (clock.getElapsedTime().asMilliseconds() >= 2000)
    return new StateMenu();
  background.draw();
  return nullptr;
}
