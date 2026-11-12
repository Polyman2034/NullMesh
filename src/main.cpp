#include <iostream>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>

    using Socket = SOCKET;
    #define INVALID_SOCKET_VALUE INVALID_SOCKET
    #define SOCKET_ERROR_VALUE SOCKET_ERROR

    int getSocketError()
    {
        return WSAGetLastError();
    }

    void closeSocket(Socket socket)
    {
        closesocket(socket);
    }

#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cerrno>

    using Socket = int;
    #define INVALID_SOCKET_VALUE (-1)
    #define SOCKET_ERROR_VALUE (-1)

    int getSocketError()
    {
        return errno;
    }

    void closeSocket(Socket socket)
    {
        close(socket);
    }
#endif

int main()
{
#ifdef _WIN32
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        std::cout << "Winsock initialization failed: "
                  << result << '\n';
        return 1;
    }

    std::cout << "Winsock initialized successfully!\n";
#endif

    Socket serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET_VALUE)
    {
        std::cout << "Socket creation failed: "
                  << getSocketError() << '\n';
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::cout << "TCP socket created successfully!\n";

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddress,
             sizeof(serverAddress)) == SOCKET_ERROR_VALUE)
    {
        std::cout << "Bind failed: " << getSocketError() << '\n';
        closeSocket(serverSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::cout << "Socket bound to port 8080!\n";

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR_VALUE)
    {
        std::cout << "Listen failed: " << getSocketError() << '\n';
        closeSocket(serverSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::cout << "Server is listening on port 8080!\n";

    sockaddr_in clientAddress{};

#ifdef _WIN32
    int clientAddressSize = sizeof(clientAddress);
#else
    socklen_t clientAddressSize = sizeof(clientAddress);
#endif

    Socket clientSocket = accept(
        serverSocket,
        (sockaddr*)&clientAddress,
        &clientAddressSize
    );

    if (clientSocket == INVALID_SOCKET_VALUE)
    {
        std::cout << "Accept failed: " << getSocketError() << '\n';
        closeSocket(serverSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::cout << "Client connected successfully!\n";

    char buffer[1024];

    auto bytesReceived = recv(
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

#ifdef _WIN32
        int bytesSent = send(
            clientSocket, response,
            static_cast<int>(strlen(response)), 0
        );
#else
        auto bytesSent = send(
            clientSocket, response,
            strlen(response), MSG_NOSIGNAL
        );
#endif

        if (bytesSent == SOCKET_ERROR_VALUE)
        {
            std::cout << "Send failed: " << getSocketError() << '\n';
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
        std::cout << "Receive failed: " << getSocketError() << '\n';
    }

    closeSocket(clientSocket);
    closeSocket(serverSocket);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
