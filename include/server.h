#pragma once

#include <set>
#include <string>

class Server {

public:
    Server(int port);

    bool Create();
    bool Bind();
    bool ListenForConnections();
    bool AcceptConnections();

    bool Run();

    bool PollClient(int clientSocket);
    bool HandleClient(int clientSocket);

private:
    int serverSocket;
    int port;
    std::set<int> clientSockets;
};