#include "WebSocketServer.hpp"
#include <iostream>

WebSocketServer::WebSocketServer(
    int port,
    GameEngine &engine,
    CommandExecutor &executor)
    : port(port),
      engine(engine),
      executor(executor)
{
}

void WebSocketServer::start()
{
    try
    {
        server.init_asio();

        server.set_open_handler(
            [this](websocketpp::connection_hdl hdl)
            {
                std::cout
                    << "SERVER CLIENT CONNECTED"
                    << std::endl;

                GameSnapshot snapshot = engine.snapshot();

                std::cout
                    << "SERVER INITIAL SNAPSHOT: "
                    << snapshot.rows
                    << " "
                    << snapshot.cols
                    << std::endl;

                std::string json = Network::Serializer::serializeSnapshot(snapshot);

                server.send(hdl, json, websocketpp::frame::opcode::text);
            });

        server.set_message_handler(
            [this](websocketpp::connection_hdl hdl, Server::message_ptr msg)
            {
                std::cout << "SERVER GOT: "
                          << msg->get_payload()
                          << std::endl;

                auto message = Network::Serializer::deserialize(msg->get_payload());

                std::cout
                    << "Received command: "
                    << message.payload
                    << std::endl;

                if (message.type == Network::MessageType::Command)
                    executor.execute(message.payload);

                GameSnapshot snapshot = engine.snapshot();
                std::cout
                    << "SERVER SNAPSHOT: "
                    << snapshot.rows
                    << " "
                    << snapshot.cols
                    << std::endl;

                std::string json = Network::Serializer::serializeSnapshot(snapshot);

                std::cout
                    << "SEND SIZE "
                    << json.size()
                    << std::endl;

                server.send(hdl, json, websocketpp::frame::opcode::text);
            });

        server.listen(port);
        server.start_accept();

        std::cout
            << "WebSocket server listening on port "
            << port
            << std::endl;

        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr
            << "WebSocket error: "
            << e.what()
            << std::endl;
    }
}