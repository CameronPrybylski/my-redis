#include <client.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   // inet_pton()
#include <unistd.h>      // close()
#include <iostream>

Client::Client(int port) : clientSocket(-1), port(port)
{
}

bool Client::Create()
{
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    return this->clientSocket != -1;
}

bool Client::Connect(std::string serverIPAddress, int serverPort)
{
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(serverPort);
    
    //Convert string for ip address to usuable bytes for sockaddr_in
    //const char* ip_addr = serverIPAddress.c_str();
    //int success = inet_pton(AF_INET, ip_addr, &addr.sin_addr);

    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);  // 127.0.0.1
    
    int rv = connect(clientSocket, (const struct sockaddr *)&addr, sizeof(addr));
    return rv > -1;
}

void Client::Send(std::string msg)
{
    const char* byteMsg = msg.c_str();
    send(clientSocket, byteMsg, strlen(byteMsg), 0);
}

void Client::Receive()
{
    char msg[64] = {};
    ssize_t bytesReceived = recv(clientSocket, msg, sizeof(msg) - 1, 0);
    if(bytesReceived < 0)
    {
        std::cerr << "Error: Client Receive" << std::endl;
    }
    else if(bytesReceived > 0)
    {
        std::string strMsg(msg);
        std::cout << "Server says: " << strMsg << std::endl;
    }
}

void Client::Disconnect()
{
    if(clientSocket > -1)
        close(clientSocket);
    clientSocket = -1;
}