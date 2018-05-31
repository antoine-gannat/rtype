
#include <SFML/Graphics/Text.hpp>
#include <stdexcept>
#include "StateMenu.hpp"
#include "StateGame.hpp"

StateMenu::StateMenu() :
  background("assets/wallpaper.jpg", 1),
  ip_hint(CORE->width / 2 - 100, CORE->height / 2),
  ip(CORE->width / 2 - 100, CORE->height / 2 + CHARACTER_SIZE + 20),
  _gameName(CORE->width / 2 - 100, 100)
{

}

StateMenu::~StateMenu()
{

}

void StateMenu::begin()
{
  ip_hint.text.setOutlineThickness(5.0);
  ip_hint.text.setOutlineColor(sf::Color::Black);
  ip_hint.text.setString("Enter IP:");
  ip.text.setOutlineThickness(5.0);
  ip.text.setOutlineColor(sf::Color::Black);
  _gameName.text.setOutlineThickness(5.0);
  _gameName.text.setOutlineColor(sf::Color::Red);
  _gameName.text.setCharacterSize(32);
  _gameName.text.setString("R-TYPE");
}

IState* StateMenu::update()
{
  try{
    if (CORE->inputs[K_RETURN])
      return new StateGame(CORE->textGet());
  } catch (std::runtime_error& e){
    std::cerr << e.what() << std::endl;
  }
  ip.text.setString(CORE->textGet());
  background.draw();
  CORE->window.draw(_gameName.text);
  CORE->window.draw(ip.text);
  CORE->window.draw(ip_hint.text);
  return nullptr;
}
