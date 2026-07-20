#pragma once


class WebSocketServer
{
public:

    explicit WebSocketServer(int port);

    void start();


private:

    int port;
};