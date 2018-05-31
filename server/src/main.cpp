#include <iostream>
#include "ServerCore.hpp"
#include "ServerNetwork.hpp"
#include "PatternLoader.hpp"

IServerNetwork* network;

int	main()
{
  srand(time(NULL));
  try {
    network = new ServerNetwork(4242);
  } catch (ServerNetworkException & e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  ServerCore core;
  core.run();

  delete network;
  PatternLoader::delInst();

  return 0;
}
