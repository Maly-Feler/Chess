#include "WebSocketServer.hpp"

#include <iostream>


WebSocketServer::WebSocketServer(int port)
    : port(port)
{
}


void WebSocketServer::start()
{
    std::cout
        << "WebSocket server started on port "
        << port
        << std::endl;
}