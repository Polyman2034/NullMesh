#include <iostream>
#include <winsock2.h>

int main()
{
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        std::cout << "WSAStartup failed: " << result << '\n';
        return 1;
    }

    std::cout << "Winsock initialized successfully!\n";

    
SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

if (serverSocket == INVALID_SOCKET)
{
    std::cout << "Socket creation failed: "
              << WSAGetLastError() << '\n';

    WSACleanup();
    return 1;
}

std::cout << "TCP socket created successfully!\n";

closesocket(serverSocket);


    WSACleanup();

    return 0;
}
