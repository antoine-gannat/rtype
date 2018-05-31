#pragma once

#include <string>
#include <unordered_map>
#include "Protocol.hpp"

class PatternLoader
{
public:
  PatternLoader();
  ~PatternLoader();
  static PatternLoader *getInst();
  static void delInst();
  Position run(std::string patternName, Position pos, int speed, Position *target);

private:
  void loadPattern(std::string patternName);

private:
  typedef CPosition (*PatternFunction)(CPosition, int, CPosition*);
  struct Pattern
  {
    PatternFunction func;
    void *handle;
  };
  std::unordered_map<std::string, Pattern> _patterns;
  static PatternLoader *_instance;
};

class PatternLoaderException : public std::runtime_error {
  public:
   PatternLoaderException() : runtime_error("PatternLoader error"){}
   PatternLoaderException(std::string msg) : runtime_error(msg.c_str()){}
 };
