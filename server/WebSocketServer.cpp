#include "WebSocketServer.hpp"
#include <iostream>

WebSocketServer::WebSocketServer(int port, CommandExecutor &executor)
    : port(port), executor(executor) {}

void WebSocketServer::start()
{
    try
    {
        server.init_asio();

        server.set_message_handler(
            [this](websocketpp::connection_hdl hdl, Server::message_ptr msg)
            {
                auto message = Network::Serializer::deserialize(msg->get_payload());

                std::cout
                    << "Received command: "
                    << message.payload
                    << std::endl;

                if (message.type == Network::MessageType::Command)
                    executor.execute(message.payload);

                server.send(hdl, msg->get_payload(), msg->get_opcode());
            });

        server.listen(port);
        server.start_accept();

        std::cout << "WebSocket server listening on port " << port << std::endl;

        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "WebSocket error: " << e.what() << std::endl;
    }
}