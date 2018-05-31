#include <exception>
#include "Core.hpp"
#include "StateMenu.hpp"
#include "StateSplash.hpp"

int main()
{
  try {
    CORE = new Core(1600, 900);
    CORE->run(new StateSplash());
    delete CORE;
  } catch (std::runtime_error &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
  return 0;
}
