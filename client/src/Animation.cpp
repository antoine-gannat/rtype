#include "Animation.hpp"

Animation::Animation(unsigned int frameX, unsigned int frameY) : _fx(frameX), _fy(frameY)
{
}

void	Animation::addFrame(unsigned int index, sf::Time delay)
{
  sf::IntRect	frame;

  frame.top = 0;
  frame.height = _fy;
  frame.width = _fx;
  frame.left = index * _fx;
  _frames.emplace_back(frame, delay);
}

const sf::IntRect	Animation::getFrame()
{
  if (_timer.getElapsedTime() >= _frames[_framePtr].delay)
    {
      _timer.restart();
      _framePtr++;
      if (_framePtr == _frames.size())
	_framePtr = 0;
    }
  return  (_frames[_framePtr].frame);
}
