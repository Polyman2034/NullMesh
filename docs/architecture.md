# NullMesh — Architecture

## 1. Project Overview

NullMesh is a TCP server built from scratch using C++ and Windows Sockets (Winsock).

The main purpose of this project is to understand how network communication works internally and how an application uses the operating system to communicate with other applications.

The server accepts client connections, receives data, and sends responses.

## 2. System Architecture

NullMesh follows a basic client-server architecture.

```text
+------------------+          +----------------------+
|                  |          |                      |
|      Client      | <------> |    NullMesh Server   |
|                  |   TCP    |                      |
+------------------+          +----------------------+
                                      |
                                      |
                               +-------------+
                               |   Winsock   |
                               +-------------+
                                      |
                                      |
                               +-------------+
                               |  Windows OS |
                               +-------------+
```

### How it works

1. The client requests a TCP connection.
2. NullMesh accepts the connection.
3. The client and server exchange data.
4. The server processes the received data.
5. The server sends a response to the client.

## 3. Main Components

### 3.1 Client

The client is the program that connects to NullMesh.

Its responsibilities are:

- Create a socket.
- Connect to the server.
- Send data.
- Receive responses.
- Close its socket.

### 3.2 TCP Server

The TCP server is the main application in NullMesh.

Its responsibilities are:

- Create a listening socket.
- Bind the socket to an IP address and port.
- Listen for incoming connections.
- Accept client connections.
- Receive client data.
- Send responses.
- Close sockets when finished.

### 3.3 Winsock

Winsock provides the functions that NullMesh uses for network communication.

Examples:

```cpp
WSAStartup();
socket();
bind();
listen();
accept();
recv();
send();
closesocket();
WSACleanup();
```

### 3.4 Windows Operating System

The Windows operating system manages the socket resources and handles the underlying network operations.

NullMesh uses Winsock to request networking operations from Windows.

## 4. TCP Server Lifecycle

The server follows this sequence:

```text
       WSAStartup()
             |
             v
          socket()
             |
             v
           bind()
             |
             v
          listen()
             |
             v
          accept()
             |
             v
           recv()
             |
             v
       Process Data
             |
             v
           send()
             |
             v
       closesocket()
             |
             v
        WSACleanup()
```

### Function Responsibilities

| Function | Responsibility |
|---|---|
| `WSAStartup()` | Initializes Winsock. |
| `socket()` | Creates a socket. |
| `bind()` | Assigns a local IP address and port. |
| `listen()` | Prepares the socket to accept connections. |
| `accept()` | Accepts a client connection. |
| `recv()` | Receives client data. |
| `send()` | Sends data to the client. |
| `closesocket()` | Closes a socket. |
| `WSACleanup()` | Cleans up Winsock resources. |

## 5. Socket Design

NullMesh uses two different sockets during normal client communication.

### Listening Socket

The listening socket waits for incoming client connections.

It is created using `socket()`, assigned an address using `bind()`, and prepared using `listen()`.

### Client Socket

When a client connects, `accept()` returns a new socket.

This socket is used to communicate with that particular client.

```text
              TCP SERVER
                  |
          +-------+-------+
          |               |
          v               |
    Listening Socket      |
          |               |
        accept()           |
          |               |
          v               |
     Client Socket        |
          |               |
       recv()/send()       |
          |               |
          v               |
        Client             |
```

The listening socket stays available to accept other clients.

## 6. Address Configuration

NullMesh uses an IPv4 address structure called `sockaddr_in`.

Example:

```cpp
sockaddr_in serverAddress{};

serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
serverAddress.sin_addr.s_addr = INADDR_ANY;
```

The server uses:

- IPv4 as the address family.
- Port `8080` as the listening port.
- `INADDR_ANY` to listen on all available local IPv4 interfaces.

## 7. Data Communication

NullMesh uses TCP to exchange data between the client and server.

The communication happens through:

- `recv()` to receive bytes.
- `send()` to send bytes.

TCP provides a continuous stream of bytes. It does not automatically separate data into application messages.

The application must decide how to identify message boundaries.

## 8. Error Handling

Network operations can fail.

NullMesh should check the return value of each important Winsock function.

Examples:

| Function | Failure indication |
|---|---|
| `WSAStartup()` | Non-zero error code |
| `socket()` | `INVALID_SOCKET` |
| `bind()` | `SOCKET_ERROR` |
| `listen()` | `SOCKET_ERROR` |
| `accept()` | `INVALID_SOCKET` |
| `recv()` | `SOCKET_ERROR` |
| `send()` | `SOCKET_ERROR` |

On Windows, `WSAGetLastError()` helps identify the reason for a failed Winsock operation.

## 9. Resource Management

Sockets use resources managed by the operating system.

NullMesh must close sockets when they are no longer needed.

The normal cleanup sequence is:

1. Close the connected client socket.
2. Close the listening socket.
3. Call `WSACleanup()` after Winsock use is finished.

## 10. Current Architecture Scope

The current architecture focuses on a basic TCP server using blocking Winsock operations.

It covers:

- IPv4 TCP socket creation.
- Local address and port binding.
- Listening for client connections.
- Accepting a client.
- Receiving and sending data.
- Closing sockets and cleaning up Winsock resources.

The architecture is intentionally kept simple so the underlying TCP communication process is easy to understand.
