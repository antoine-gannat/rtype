#include "Animation.hpp"
#include "StateOver.hpp"
#include "StateMenu.hpp"

StateOver::StateOver() :
  background("assets/over.png", 1)
{
  
}

StateOver::~StateOver()
{

}

void StateOver::begin()
{
}

IState* StateOver::update()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    return new StateMenu();
  background.draw();
  return nullptr;
}
