#pragma once

#include "WebSocketServer.hpp"


class NetworkServer
{
public:

    explicit NetworkServer(int port);

    void start();


private:

    int port;

    WebSocketServer websocketServer;
};