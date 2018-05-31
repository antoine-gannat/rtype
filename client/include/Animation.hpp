#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:

  struct Frame
  {
    Frame(const sf::IntRect& _frame, sf::Time _delay) :
      frame(_frame), delay(_delay)
    {
    }

    sf::IntRect	frame;
    sf::Time	delay;
  };

  Animation(unsigned int frameX, unsigned int frameY);

  void addFrame(unsigned int index, sf::Time delay);
  const sf::IntRect getFrame();

private:
  std::vector<Frame> _frames;

  sf::Clock		_timer;
  unsigned		_framePtr = 0;
  const unsigned int	_fx;
  const unsigned int	_fy;
};
