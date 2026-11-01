#include <server.h>

#include <sys/socket.h>  // socket()
#include <netinet/in.h>  // sockaddr_in

#include <iostream>

Server::Server(int port) : serverSocket(-1), port(port)
{

}

bool Server::Create()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket > -1)
    {
        int val = 1;
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    }
    return serverSocket != -1;
}

bool Server::Bind()
{
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);        // port
    addr.sin_addr.s_addr = htonl(0);    // wildcard IP 0.0.0.0
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);    // localhost IP 127.0.0.1
    //INADDR_LOOPBACK
    int rv = bind(serverSocket, (const struct sockaddr *)&addr, sizeof(addr));
    return rv != -1;
}

bool Server::ListenForConnections()
{
    int success = listen(serverSocket, SOMAXCONN);
    return success > -1;
}

bool Server::AcceptConnections()
{
    struct sockaddr_in client_addr = {};
    socklen_t addrlen = sizeof(client_addr);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&client_addr, &addrlen);
    if(clientSocket > -1)
    {
        clientSockets.insert(clientSocket);
        return true;
    }
    return false;
}

bool Server::Run()
{
    if(!(Create() && Bind() && ListenForConnections()))
    {
        return false;
    }
    while(true)
    {
        AcceptConnections();

        std::set<int>::iterator clientSocket = clientSockets.begin();
        for(; clientSocket != clientSockets.end();)
        {
            if(HandleClient(*clientSocket))
            {
                clientSocket = clientSockets.erase(clientSocket);
            }
            else
            {
                ++clientSocket;
            }
        }
    }
}

bool Server::PollClient(int clientSocket)
{
    return true;
}

bool Server::HandleClient(int clientSocket)
{
    char buffer[64] = {};
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if(bytesReceived > 0)
    {
        char msg[] = "goodbye";
        send(clientSocket, msg, strlen(msg), 0);
    }
    else if(bytesReceived == 0)
    {
        std::cout << "Client: " << clientSocket << " disconnected" << std::endl;
        return true;
    }
    return false;
}
