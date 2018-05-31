#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include "Protocol.hpp"
#include "IState.hpp"
#include "Text.hpp"
#include "EntityManager.hpp"
#include "ClientNetwork.hpp"

#define CHARACTER_SIZE 24

struct keysConvert
{
  char key;
  Protocol::PlayerKeys convKey;
};

enum E_INPUT
  {
    K_UNK = 0,
    K_RETURN,
    K_MOUSE_LEFT,
    K_MOUSE_RIGHT,
    K_MAX
  };

class Core
{
protected:
  bool running;
  IState *state;
  std::string input_text;
public:
  sf::RenderWindow window;
  int width;
  int height;
  //inputs
  bool inputs[K_MAX];//Only non repeating inputs
public:
  Core(int _width, int _height);
  virtual ~Core();
  void run(IState *begin_state);
  void stop();
  void textReset();
  std::string textGet();
  void sendKeyPressed(char key);
};

extern Core* CORE;
