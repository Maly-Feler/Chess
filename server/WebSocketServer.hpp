// #pragma once
// #include <websocketpp/config/asio_no_tls.hpp>
// #include <websocketpp/server.hpp>

// class WebSocketServer
// {
// public:

//     explicit WebSocketServer(int port);

//     void start();

// private:

//     using Server = websocketpp::server<websocketpp::config::asio>;

//     Server server;

//     int port;
// };

// #pragma once

// // #define ASIO_STANDALONE
// // #define _WEBSOCKETPP_CPP11_STL_

// #include <websocketpp/config/asio_no_tls.hpp>
// #include <websocketpp/server.hpp>
// #include "../src/commands/CommandExecutor.hpp"
// #include <string>

// class WebSocketServer
// {
// public:

//     WebSocketServer(int port, CommandExecutor& executor);
//     void start();

// private:

//     using Server = websocketpp::server<websocketpp::config::asio>;

//     Server server;
//     int port;
// };

#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "../src/network/Serializer.hpp"
#include "../src/commands/CommandExecutor.hpp"
#include "../src/game_engine/GameEngine.hpp"

class WebSocketServer
{
public:
    WebSocketServer(int port, GameEngine &engine, CommandExecutor &executor);

    void start();

private:
    using Server = websocketpp::server<websocketpp::config::asio>;

    Server server;
    int port;

    GameEngine &engine;
    CommandExecutor &executor;
};