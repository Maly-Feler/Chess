#include "NetworkServer.hpp"

#include <iostream>

NetworkServer::NetworkServer(int port, CommandExecutor& executor) : websocketServer(port, executor) {}

void NetworkServer::start()
{
    std::cout
        << "Network server starting..."
        << std::endl;

    websocketServer.start();
}