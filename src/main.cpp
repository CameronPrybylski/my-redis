#include <iostream>
#include <server.h>

int main()
{
    std::cout << "Hello, My Redis" << std::endl;
    Server server(1234);
    server.Run();
    return 0;
}