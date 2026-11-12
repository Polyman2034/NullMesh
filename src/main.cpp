#include <iostream>
#include <winsock2.h>
#include <cstring>

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
    
sockaddr_in serverAddress{};

serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
serverAddress.sin_addr.s_addr = INADDR_ANY;

if (bind(serverSocket, (sockaddr*)&serverAddress,
         sizeof(serverAddress)) == SOCKET_ERROR)
{
    std::cout << "Bind failed: "
              << WSAGetLastError() << '\n';

    closesocket(serverSocket);
    WSACleanup();
    return 1;
}

std::cout << "Socket bound to port 8080!\n";
    
if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
{
    std::cout << "Listen failed: "
              << WSAGetLastError() << '\n';

    closesocket(serverSocket);
    WSACleanup();
    return 1;
}

std::cout << "Server is listening on port 8080!\n";
sockaddr_in clientAddress{};
int clientAddressSize = sizeof(clientAddress);

SOCKET clientSocket = accept(
    serverSocket,
    (sockaddr*)&clientAddress,
    &clientAddressSize
);

if (clientSocket == INVALID_SOCKET)
{
    std::cout << "Accept failed: "
              << WSAGetLastError() << '\n';

    closesocket(serverSocket);
    WSACleanup();
    return 1;
}

std::cout << "Client connected successfully!\n";
    
char buffer[1024];

int bytesReceived = recv(
    clientSocket,
    buffer,
    sizeof(buffer) - 1,
    0
);

if (bytesReceived > 0)
{
    buffer[bytesReceived] = '\0';

    std::cout << "Client says: " << buffer << '\n';
    
const char* response = "Message received by NullMesh!\n";

int bytesSent = send(
    clientSocket,
    response,
    static_cast<int>(strlen(response)),
    0
);

if (bytesSent == SOCKET_ERROR)
{
    std::cout << "Send failed: "
              << WSAGetLastError() << '\n';
}
else
{
    std::cout << "Response sent to client!\n";
}

}
else if (bytesReceived == 0)
{
    std::cout << "Client disconnected.\n";
}
else
{
    std::cout << "Receive failed: "
              << WSAGetLastError() << '\n';
}


closesocket(clientSocket);




closesocket(serverSocket);


    WSACleanup();

    return 0;
}
