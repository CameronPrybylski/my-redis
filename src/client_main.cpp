#include <iostream>

#include <client.h>

int main()
{
    Client client(1235);
    client.Create();
    if(client.Connect("127.0.0.1", 1234))
    {
        client.Send("Hello");
        client.Receive();
        client.Disconnect();
    }
    return 0;
}