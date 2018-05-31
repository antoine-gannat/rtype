#include <stdexcept>
#include <ctype.h>
#include <SFML/Audio.hpp>
#include "Core.hpp"
#include "EntityManager.hpp"

Core* CORE = nullptr;

Core::Core(int _width, int _height) :
  width(_width),
  height(_height),
  running(false),
  state(nullptr)
{
  window.create(sf::VideoMode(width, height), "RType");
  window.setFramerateLimit(60);
}

Core::~Core()
{
}

void Core::run(IState *begin_state)
{
  sf::Music music;
  if (!music.openFromFile("assets/music.ogg"))
    {
      std::cout << "Error loading music" << std::endl;
      return;
    }
  music.play();
  IState *buff_state;
  if (running)
    throw std::runtime_error("Already runnning");
  running = true;
  state = begin_state;
  state->begin();
  while (window.isOpen() && running)
    {
      sf::Event event;
      std::memset(inputs, 0, K_MAX);
      while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed)
            window.close();
	  if (event.type == sf::Event::MouseButtonPressed)
	    {
	      inputs[K_MOUSE_LEFT] = (event.mouseButton.button == sf::Mouse::Left);
	      inputs[K_MOUSE_RIGHT] = (event.mouseButton.button == sf::Mouse::Right);
	    }
	  char c;
	  if (event.type == sf::Event::TextEntered)
	    {
	      c = static_cast<char>(event.text.unicode);
	      if (isprint(c))
		input_text += c;
	      else if (c == '\b' && input_text.size())
		input_text = input_text.substr(0, input_text.size() - 1);
	      else if (c == '\r')
		inputs[K_RETURN] = true;
	      //std::cout << input_text << std::endl;
	    }
	}
      window.clear();
      buff_state = state->update();
      if (buff_state)
	{
	  delete state;
	  state = buff_state;
	  input_text = "";
	  state->begin();
	}
      window.display();
    }
}

void Core::stop()
{
  running = false;
}

void Core::textReset()
{
  input_text = "";
}

std::string Core::textGet()
{
  return input_text;
}
