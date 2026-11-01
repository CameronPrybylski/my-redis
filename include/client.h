#pragma once

#include <string>

class Client {
public:
    Client(int port);

    bool Create();
    bool Connect(std::string ipAddress, int port);

    void Send(std::string msg);
    void Receive();

    void Disconnect();
private:
    int clientSocket;
    int port;
};