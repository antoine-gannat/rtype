#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include "PatternLoader.hpp"

PatternLoader::PatternLoader() {}

PatternLoader::~PatternLoader()
{
  for (auto it : _patterns)
  {
    #if defined(_WIN32) || defined(WIN32)
    FreeLibrary((HMODULE)it.second.handle);
    #else
    dlclose(it.second.handle);
    #endif
  }
}

Position PatternLoader::run(std::string patternName, Position pos, int speed, Position *target)
{
  if (_patterns.find(patternName) == _patterns.end())
    loadPattern(patternName);
  CPosition t;
  t.x = target->x;
  t.y = target->y;
  CPosition p = (_patterns[patternName].func)(pos.toC(), speed, &t);
  target->x = t.x;
  target->y = t.y;
  pos.x = p.x;
  pos.y = p.y;
  return pos;
}

#if defined(_WIN32) || defined(WIN32)
void PatternLoader::loadPattern(std::string patternName)
{
  Pattern pattern;
  void *sym;
  std::string libPath;

  libPath = "Pattern" + patternName + ".dll";
  pattern.handle = LoadLibrary(libPath.c_str());
  if (!pattern.handle)
    throw PatternLoaderException(std::string("PatternLoader: LoadLibrary failed"));
  sym = GetProcAddress((HMODULE)pattern.handle, "pattern");
  if (!sym)
    throw PatternLoaderException(std::string("PatternLoader: GetProcAddress failed"));
  pattern.func = (PatternFunction)sym;
  _patterns[patternName] = pattern;
}
#else
void PatternLoader::loadPattern(std::string patternName)
{
  Pattern pattern;
  const char *errorMsg;
  void *sym;
  std::string libPath;

  libPath = "./patterns/libPattern" + patternName + ".so";
  pattern.handle = dlopen(libPath.c_str(), RTLD_LAZY);
  errorMsg = dlerror();
  if (!pattern.handle)
    throw PatternLoaderException(std::string("PatternLoader: ") + errorMsg);
  sym = dlsym(pattern.handle, "pattern");
  errorMsg = dlerror();
  if (errorMsg)
    throw PatternLoaderException(std::string("PatternLoader: ") + errorMsg);
  pattern.func = (PatternFunction)sym;
  _patterns[patternName] = pattern;
}
#endif

PatternLoader *PatternLoader::_instance = nullptr;

PatternLoader *PatternLoader::getInst()
{
  if (_instance == nullptr)
    _instance = new PatternLoader();
  return _instance;
}

 void PatternLoader::delInst()
 {
   if (_instance != nullptr)
    delete _instance;
 }
