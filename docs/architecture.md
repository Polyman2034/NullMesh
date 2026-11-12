# NullMesh — Architecture

## 1. Project Overview

NullMesh is a TCP server built from scratch using C++17 and operating-system socket APIs.

The project aims to understand how network communication works internally and how an application uses the operating system to communicate with other applications.

The server creates a TCP socket, binds it to a local port, listens for incoming connections, accepts a client, receives data, and sends a response.

NullMesh currently supports:

- Windows using Winsock.
- Linux using POSIX sockets.

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
                             +-------------------+
                             | Socket API Layer  |
                             +-------------------+
                                      |
                         +------------+------------+
                         |                         |
                         v                         v
                  +-------------+           +-------------+
                  |   Winsock   |           | POSIX       |
                  |   Windows  |           | Linux       |
                  +-------------+           +-------------+
```

### How it works

1. The server initializes its networking environment where required.
2. The server creates a TCP socket.
3. The socket is bound to a local address and port.
4. The server starts listening for connections.
5. A client connects and the server accepts the connection.
6. The server receives client data.
7. The server sends a response.
8. Both sockets are closed and platform-specific resources are cleaned up.

## 3. Main Components

### 3.1 Client

The client is the program that connects to NullMesh.

Its responsibilities are:

- Create a socket.
- Connect to the server.
- Send data.
- Receive responses.
- Close its socket.

A Python socket client is currently used to test communication with the C++ server.

### 3.2 TCP Server

The TCP server is the main application in NullMesh.

Its responsibilities are:

- Create a listening socket.
- Bind the socket to an IP address and port.
- Listen for incoming connections.
- Accept a client connection.
- Receive client data.
- Send a response.
- Close sockets when finished.

### 3.3 Platform Socket APIs

NullMesh uses different socket APIs depending on the operating system.

**Windows — Winsock**

- `WSAStartup()`
- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `recv()`
- `send()`
- `closesocket()`
- `WSACleanup()`

**Linux — POSIX sockets**

- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `recv()`
- `send()`
- `close()`

Linux uses `errno` to report socket errors, while Windows uses `WSAGetLastError()` for Winsock errors.

### 3.4 Operating System

The operating system manages socket resources and performs the underlying network operations.

NullMesh requests these operations through the platform's socket API.

## 4. TCP Server Lifecycle

The current server follows this sequence:

```text
          Windows only
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
       Close Client Socket
                |
                v
      Close Listening Socket
                |
                v
          Windows only
          WSACleanup()
```

### Function Responsibilities

| Function | Responsibility |
|---|---|
| `WSAStartup()` | Initializes Winsock on Windows. |
| `socket()` | Creates a socket. |
| `bind()` | Assigns a local IP address and port. |
| `listen()` | Prepares the socket to accept connections. |
| `accept()` | Accepts a client connection. |
| `recv()` | Receives data from the client. |
| `send()` | Sends data to the client. |
| `closesocket()` | Closes a socket on Windows. |
| `close()` | Closes a socket on Linux. |
| `WSACleanup()` | Cleans up Winsock resources on Windows. |

## 5. Socket Design

NullMesh uses two sockets during client communication.

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
        Client
```

**Current implementation:** The server accepts one client connection, communicates with it, and then closes both sockets. The listening socket is not yet reused to accept additional clients.

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

`htons()` converts the port number into network byte order.

## 7. Data Communication

NullMesh uses TCP to exchange data between the client and server.

Communication happens through:

- `recv()` to receive bytes.
- `send()` to send bytes.

TCP provides a continuous stream of bytes. It does not automatically separate data into application messages.

The current implementation performs one receive operation and one send operation. It does not yet handle partial transfers or implement application-level message framing.

## 8. Error Handling

Network operations can fail. NullMesh checks the return values of important socket functions.

### Windows

| Function | Failure indication |
|---|---|
| `WSAStartup()` | Non-zero error code |
| `socket()` | `INVALID_SOCKET` |
| `bind()` | `SOCKET_ERROR` |
| `listen()` | `SOCKET_ERROR` |
| `accept()` | `INVALID_SOCKET` |
| `recv()` | `SOCKET_ERROR` |
| `send()` | `SOCKET_ERROR` |

`WSAGetLastError()` provides the error code for failed Winsock operations.

### Linux

| Function | Failure indication |
|---|---|
| `socket()` | `-1` |
| `bind()` | `-1` |
| `listen()` | `-1` |
| `accept()` | `-1` |
| `recv()` | `-1` |
| `send()` | `-1` |

Linux socket errors are reported through `errno`.

## 9. Resource Management

Sockets use resources managed by the operating system.

NullMesh closes sockets when they are no longer needed.

The cleanup sequence is:

1. Close the connected client socket.
2. Close the listening socket.
3. Call `WSACleanup()` on Windows after Winsock use is finished.

Linux uses `close()` instead of `closesocket()` and does not require `WSACleanup()`.

## 10. Current Architecture Scope

The current architecture focuses on a basic, blocking TCP server.

It covers:

- IPv4 TCP socket creation.
- Cross-platform socket handling.
- Local address and port binding.
- Listening for client connections.
- Accepting one client.
- Receiving and sending data.
- Closing sockets and cleaning up resources.

The implementation has been compiled and tested in GitHub Codespaces on Linux using a Python socket client.

The architecture is intentionally kept simple so the underlying TCP communication process is easy to understand.

Future improvements include multiple-client handling, reliable data transmission, and HTTP request handling.
