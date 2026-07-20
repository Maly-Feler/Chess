#pragma once

#include "WebSocketServer.hpp"
#include "../src/commands/CommandExecutor.hpp"


class NetworkServer
{
public:

    NetworkServer(int port,CommandExecutor& executor);
    void start();


private:

    WebSocketServer websocketServer;
};