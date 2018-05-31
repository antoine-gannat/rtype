#include "Animation.hpp"
#include "StatePlay.hpp"

StatePlay::StatePlay() : _anim(33, 36)
{

}

StatePlay::~StatePlay()
{

}

void StatePlay::begin()
{
  if (!_texture.loadFromFile("assets/textures/enemy.png"))
    throw std::runtime_error("Can't load asset");
  _animSprite.setTexture(&_texture);
  _animSprite.setSize({100, 100});

  for (int i = 0; i < 8/*nb frames*/ ; i++)
    {
      _anim.addFrame(i, sf::seconds(0.1));
    }
}

IState* StatePlay::update()
{
  _animSprite.setTextureRect(_anim.getFrame());
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      _animSprite.move(0, -3.0f);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      _animSprite.move(0, 3.0f);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      _animSprite.move(-3.0f, 0);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      _animSprite.move(3.0f, 0);
    }
  CORE->window.draw(_animSprite);
  return nullptr;
}
