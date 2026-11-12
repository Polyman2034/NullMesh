# Learning Notes — NullMesh

# Part 1: Networking Fundamentals

## 1. What is a Server?

A server is a program that provides a service to other programs.

It waits for requests, does the required work, and sends back a response.

**Example:** When you open a website, your browser requests a webpage from a server. The server sends the webpage back.

A server is a program, not necessarily a separate computer.

## 2. Client-Server Communication

Client-server communication means one program requests something, and another program provides it.

- **Client:** The program that asks for something.
- **Server:** The program that receives the request and responds.

```text
Client
   |
   | Request
   v
Server
   |
   | Response
   v
Client
```

**Example:** Your browser is the client, and the website's server provides the webpage.

## 3. Network and Network Connection

**Network:** A group of connected devices that can communicate with each other.

**Network connection:** A communication link between two endpoints.

Think of a network as a road system and a connection as a particular journey between two places.

## 4. IP Address

An IP address is an address used to identify a network interface and help data reach the correct destination.

**Example:**

```text
127.0.0.1
```

`127.0.0.1` is called the loopback address. It refers to your own computer.

**Remember:** An IP address helps identify where the data should go.

## 5. Port

A port is a number used to identify a communication endpoint on a computer.

One computer can run many network applications. Ports help TCP or UDP deliver data to the correct application endpoint.

**Example:**

```text
IP Address: 127.0.0.1
Port:       8080
```

**Remember:**
- IP address = Which network interface?
- Port = Which communication endpoint?

A port is a number, not a physical hole or connection point.

## 6. Socket

A socket is a communication endpoint provided by the operating system.

A program uses a socket to send and receive data over a network.

**Example:** Think of a socket as a communication door that your program uses to talk to another program.

**Purpose:** It allows your program to use the operating system's networking facilities.

## 7. File Descriptor and Socket Handle

The operating system manages resources such as files and sockets.

A program needs a way to refer to these resources. The operating system provides identifiers for this purpose.

**On Linux:**
- These identifiers are commonly called file descriptors.
- A socket is represented by an integer file descriptor.

**On Windows:**
- A socket is represented by a `SOCKET` handle.
- Winsock provides functions to work with it.

**Remember:** A file descriptor or socket handle is an identifier that lets a program refer to a resource managed by the operating system.

## 8. TCP (Transmission Control Protocol)

TCP is a protocol that allows two programs to communicate reliably over a network.

It provides:

- **Reliable delivery:** TCP works to ensure data reaches the other endpoint.
- **Correct order:** Data is delivered to the application in the order it was sent.
- **Retransmission:** Lost data can be sent again.
- **Flow control:** Helps prevent a sender from overwhelming the receiver.
- **Congestion control:** Helps reduce network overload.

**Example:** If you send `HELLO`, TCP makes sure the receiving application gets the bytes in the correct order.

**Important:** TCP sends a continuous stream of bytes. It does not automatically separate your data into messages.

## 9. TCP Connection

A TCP connection is an established communication relationship between two endpoints.

Each connection is identified by four values:

1. Client IP address.
2. Client port.
3. Server IP address.
4. Server port.

### TCP Three-Way Handshake

Before exchanging data, TCP establishes a connection using three steps.

```text
Client                  Server
   |                       |
   |-------- SYN --------->|
   |                       |
   |<----- SYN + ACK ------|
   |                       |
   |-------- ACK --------->|
   |                       |
   |   Connection Ready    |
```

1. **SYN:** The client asks to start a connection.
2. **SYN-ACK:** The server acknowledges the request and responds.
3. **ACK:** The client acknowledges the server's response.

After these steps, the TCP connection is established.

---

# Part 2: TCP Server

## 1. What is a TCP Server?

A TCP server is a program that waits for clients to connect using TCP.

After accepting a connection, it can receive data from the client and send data back.

```text
Client  <========== TCP Connection ==========>  Server
```

## 2. Why Do We Need a TCP Server?

Two programs may need to exchange data even when they are running on different computers.

A TCP server allows one program to wait for connections and communicate with clients reliably.

**Examples:**
- A web server communicates with browsers.
- A database server communicates with applications.
- A file server communicates with file-transfer clients.

## 3. What Does a TCP Server Do?

A basic TCP server performs these operations:

1. Initializes the networking library when required by the operating system.
2. Creates a socket.
3. Gives the socket a local IP address and port.
4. Prepares the socket to receive connection requests.
5. Accepts a client's connection.
6. Receives data from the client.
7. Processes the data.
8. Sends a response.
9. Closes the sockets and releases networking resources.

## 4. TCP Server Lifecycle

The networking initialization and cleanup steps differ between Windows and Linux.

**Windows — Winsock:**

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
   send()
     |
     v
closesocket()
     |
     v
WSACleanup()
```

**Linux — POSIX sockets:**

```text
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
   send()
     |
     v
   close()
```

Linux does not require `WSAStartup()` or `WSACleanup()`.

Each function has a different job.

---

# Part 3: Socket Programming on Windows and Linux

## 1. Winsock

Winsock means Windows Sockets.

It is the Windows programming interface used to create sockets and communicate over networks.

It provides functions such as:

```cpp
WSAStartup()
socket()
bind()
listen()
accept()
recv()
send()
closesocket()
WSACleanup()
```

## 2. POSIX Sockets

POSIX sockets are the standard socket programming interface commonly used on Linux and other Unix-like systems.

They provide functions such as:

```cpp
socket()
bind()
listen()
accept()
recv()
send()
close()
```

**Simple meaning:** Winsock is the Windows socket interface, while POSIX sockets are used on Linux and other Unix-like systems.

## 3. WSAStartup()

Before using Winsock, a Windows program must initialize it.

`WSAStartup()` performs this initialization.

**Simple meaning:** Prepare Windows networking so the program can use socket functions.

Example:

```cpp
WSADATA wsaData;

int result = WSAStartup(
    MAKEWORD(2, 2),
    &wsaData
);
```

- `MAKEWORD(2, 2)` requests Winsock version 2.2.
- `WSADATA` stores information about the initialized Winsock library.
- The return value indicates whether initialization succeeded.

**Important:** This function is required on Windows, not Linux.

## 4. WSACleanup()

`WSACleanup()` tells Winsock that the program has finished using it.

**Simple meaning:** Clean up Winsock after networking work is finished.

It is used on Windows after the program has finished using its sockets.

**Important:** Linux does not have this Winsock cleanup step.

## 5. SOCKET and File Descriptor

The socket identifier has a different type on each operating system.

**Windows:**

```cpp
SOCKET serverSocket;
```

**Linux:**

```cpp
int serverSocket;
```

Windows uses the `SOCKET` type, while Linux represents a socket using an integer file descriptor.

In NullMesh, a common type alias is used to make the code easier to share:

```cpp
#ifdef _WIN32
    using Socket = SOCKET;
#else
    using Socket = int;
#endif
```

This allows the rest of the code to use `Socket` without repeatedly writing different types.

## 6. Invalid Socket

The operating systems use different values to indicate socket creation failure.

**Windows:**

```cpp
INVALID_SOCKET
```

**Linux:**

```cpp
-1
```

NullMesh defines a common invalid socket value:

```cpp
#ifdef _WIN32
    #define INVALID_SOCKET_VALUE INVALID_SOCKET
#else
    #define INVALID_SOCKET_VALUE (-1)
#endif
```

This lets the program check socket creation failure using one common condition.

## 7. Socket Errors

The operating systems also provide different ways to retrieve socket error information.

**Windows:**

```cpp
WSAGetLastError();
```

**Linux:**

```cpp
errno;
```

In NullMesh, a helper function is used:

```cpp
#ifdef _WIN32
    int getSocketError()
    {
        return WSAGetLastError();
    }
#else
    int getSocketError()
    {
        return errno;
    }
#endif
```

**Simple meaning:** Get the operating system's error code when a socket operation fails.

## 8. Closing a Socket

The function used to close a socket differs between Windows and Linux.

**Windows:**

```cpp
closesocket(serverSocket);
```

**Linux:**

```cpp
close(serverSocket);
```

NullMesh uses a common helper:

```cpp
#ifdef _WIN32
    void closeSocket(Socket socket)
    {
        closesocket(socket);
    }
#else
    void closeSocket(Socket socket)
    {
        close(socket);
    }
#endif
```

**Remember:**

| Operation | Windows | Linux |
|---|---|---|
| Socket type | `SOCKET` | `int` |
| Invalid socket | `INVALID_SOCKET` | `-1` |
| Get socket error | `WSAGetLastError()` | `errno` |
| Close socket | `closesocket()` | `close()` |
| Initialize networking | `WSAStartup()` | Not required |
| Cleanup networking | `WSACleanup()` | Not required |

---

# Part 4: Creating and Configuring a Socket

## 1. socket()

`socket()` asks the operating system to create a new socket.

The operating system creates the socket and gives the program a socket handle or file descriptor.

Example:

```cpp
Socket serverSocket = socket(
    AF_INET,
    SOCK_STREAM,
    IPPROTO_TCP
);
```

### What do these parameters mean?

**AF_INET**

Use IPv4 addresses.

**SOCK_STREAM**

Create a stream-based socket. TCP commonly uses this type.

**IPPROTO_TCP**

Use the TCP protocol.

Together, these parameters request an IPv4 TCP socket.

## 2. sockaddr_in

`sockaddr_in` is a structure used to store an IPv4 address and port.

Example:

```cpp
sockaddr_in serverAddress{};

serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
serverAddress.sin_addr.s_addr = INADDR_ANY;
```

It stores three important things:

- `sin_family`: Which address type to use, such as IPv4.
- `sin_port`: Which port the server will use.
- `sin_addr`: Which local IP address the server will use.

**Simple meaning:** This structure holds the address information that we want to give to our socket.

## 3. htons()

Computers can store numbers in different byte orders.

Networks use a standard byte order called network byte order.

`htons()` converts a 16-bit number from the computer's byte order into network byte order.

Example:

```cpp
serverAddress.sin_port = htons(8080);
```

**Simple meaning:** Convert the port number into the format expected by the network.

## 4. INADDR_ANY

`INADDR_ANY` means the server can listen on all available local IPv4 network interfaces.

Example:

```cpp
serverAddress.sin_addr.s_addr = INADDR_ANY;
```

**Simple meaning:** Do not restrict the server to just one local IPv4 interface.

## 5. bind()

`bind()` connects a socket to a local IP address and port number.

Example:

```cpp
bind(
    serverSocket,
    (sockaddr*)&serverAddress,
    sizeof(serverAddress)
);
```

**Why do we need it?**

The server needs to tell the operating system which local address and port it wants to use.

**Simple meaning:** Give the socket its local address and port.

## 6. listen()

`listen()` tells the operating system that this socket will be used to wait for incoming TCP connections.

Example:

```cpp
listen(serverSocket, SOMAXCONN);
```

The second parameter is the requested backlog size for pending connections.

**Why do we need it?**

After binding the socket, the server needs to prepare it to receive connection requests.

**Simple meaning:** Put the socket into listening mode.

**Important:** `listen()` does not accept a client. It only prepares the socket to accept connections.

## 7. accept()

`accept()` accepts an incoming client connection.

Example:

```cpp
Socket clientSocket = accept(
    serverSocket,
    nullptr,
    nullptr
);
```

When a client connects, `accept()` returns a new socket.

This new socket is used to communicate with that client.

### Why are there two sockets?

**serverSocket:**
- Waits for incoming connections.
- Remains available to accept more clients.

**clientSocket:**
- Represents an accepted client connection.
- Used to receive and send data.

**Simple example:** The listening socket is like the reception desk. When a visitor arrives, a separate communication channel is created for that visitor.

---

# Part 5: Sending and Receiving Data

## 1. recv()

`recv()` receives data from a connected socket.

Example:

```cpp
char buffer[1024];

auto bytesReceived = recv(
    clientSocket,
    buffer,
    sizeof(buffer) - 1,
    0
);
```

### What do the parameters mean?

- `clientSocket`: From which connection should data be received?
- `buffer`: Where should the received data be stored?
- `sizeof(buffer) - 1`: What is the maximum number of bytes to receive?
- `0`: No special receive flags.

The extra byte is reserved so the received data can be terminated with `'\0'` when treating it as a C-style string.

### What does recv() return?

- **Positive number:** Number of bytes received.
- **0:** The other side has gracefully closed its sending direction.
- **Error value:** Something went wrong.

The error value is `SOCKET_ERROR` on Windows and `-1` on Linux.

**Important:** If the buffer can hold 1023 bytes, `recv()` does not have to return all 1023 bytes. It may return fewer.

## 2. send()

`send()` sends data through a connected socket.

Example:

```cpp
const char* message = "Hello Client";

auto bytesSent = send(
    clientSocket,
    message,
    strlen(message),
    0
);
```

### What do the parameters mean?

- `clientSocket`: Through which connection should data be sent?
- `message`: What data should be sent?
- `strlen(message)`: How many bytes should be sent?
- `0`: No special sending flags.

### What does send() return?

- **Positive number:** Number of bytes accepted for sending.
- **Error value:** The operation failed.

The error value is `SOCKET_ERROR` on Windows and `-1` on Linux.

**Important:** A successful `send()` does not mean the other program has already received or processed all the data.

Sometimes `send()` sends fewer bytes than requested. The program must handle this if it needs to send the complete message.

## 3. TCP Byte Stream

TCP sends data as a continuous stream of bytes.

It does not understand where one message ends and another begins.

**Example:**

The sender calls `send()` twice:

```text
First send:  Hello
Second send: World
```

The receiver might get:

```text
HelloWorld
```

Or it might receive the data in separate parts.

TCP does not promise that one `send()` call will match one `recv()` call.

**Simple meaning:** TCP delivers bytes, not ready-made messages.

The application must decide how to separate messages. Common methods include:

- Fixed-size messages.
- A special ending character, such as `\n`.
- Sending the message length before its data.

## 4. Blocking Socket Operations

A blocking operation waits until it can make progress, completes, or fails.

For example:

- `accept()` waits for a client connection.
- `recv()` waits for data when no data is available.
- `send()` may wait when the sending buffer does not have enough space.

**Simple meaning:** The program waits instead of immediately moving on.

Blocking sockets are useful when learning a basic TCP server because the communication flow is easier to understand.

## 5. Listening Socket vs Connected Socket

| Listening Socket | Connected Socket |
|---|---|
| Waits for client connections. | Communicates with an accepted client. |
| Created using `socket()`. | Returned by `accept()`. |
| Used with `bind()` and `listen()`. | Used with `recv()` and `send()`. |
| Can accept multiple clients over time. | Represents one particular connection. |

**NullMesh currently:** The server accepts one client, communicates with it, and then closes both sockets. It does not currently loop to accept additional clients.

## 6. MSG_NOSIGNAL on Linux

Linux provides the `MSG_NOSIGNAL` flag for `send()`.

Example:

```cpp
send(
    clientSocket,
    message,
    strlen(message),
    MSG_NOSIGNAL
);
```

It prevents a `SIGPIPE` signal from being generated when sending to a connection whose other end has been closed.

NullMesh uses this flag in its Linux implementation.

The Windows implementation uses `0` for the send flags.

---

# Part 6: Closing Connections and Cleaning Up

## 1. Closing a Socket

The socket closing function depends on the operating system.

**Windows:**

```cpp
closesocket(clientSocket);
```

**Linux:**

```cpp
close(clientSocket);
```

A server generally closes the client socket when it has finished communicating with that client.

It closes the listening socket when the server is shutting down.

## 2. TCP Connection Closing

TCP has a process for closing a connection gracefully.

A common closing sequence uses four messages:

```text
Client                  Server
   |                       |
   |-------- FIN --------->|
   |                       |
   |<------- ACK ----------|
   |                       |
   |<------- FIN ----------|
   |                       |
   |-------- ACK --------->|
   |                       |
   |    Connection Closed  |
```

- **FIN:** An endpoint says it has finished sending data.
- **ACK:** The other endpoint acknowledges that message.

This process allows both sides to finish sending data before the connection is fully closed.

The exact sequence can vary depending on how the connection is closed.

## 3. Resource Cleanup

Sockets are resources managed by the operating system.

When the program no longer needs a socket, it should close it.

A normal Windows cleanup order is:

1. Close the connected client socket.
2. Close the listening socket.
3. Call `WSACleanup()` after Winsock use is finished.

A normal Linux cleanup order is:

1. Close the connected client socket.
2. Close the listening socket.

**Why?** To release resources instead of leaving them unnecessarily allocated.

---

# Part 7: Complete TCP Client-Server Communication

The following diagram shows how a basic TCP client and server communicate.

```text
             SERVER                         CLIENT

        WSAStartup()                    socket()
             |                             |
          socket()                      connect()
             |                             |
           bind()                          |
             |                             |
          listen()                         |
             |                             |
          accept() <-----------------------|
             |
        TCP Connection
             |
           recv() <---------------- Client Data
             |
        Process Data
             |
           send() ----------------> Server Response
             |
       Close Client Socket           Close Client Socket
             |
      Close Listening Socket
             |
        WSACleanup()
```

### What happens here?

1. The Windows server initializes Winsock. The Linux server does not need this step.
2. Both programs create their sockets.
3. The server assigns its socket a local address and port using `bind()`.
4. The server calls `listen()` to wait for clients.
5. The client calls `connect()` to request a connection.
6. The server calls `accept()` to accept the client.
7. Both programs now have a TCP connection.
8. The client and server exchange data using `send()` and `recv()`.
9. Both programs close their sockets.
10. The Windows server calls `WSACleanup()` after finishing its Winsock operations.

---

# Part 8: NullMesh Current TCP Server Architecture

## 1. Platform Support

NullMesh uses C++17 and supports two socket programming interfaces:

- **Windows:** Winsock.
- **Linux:** POSIX sockets.

The operating-system-specific code is selected using preprocessor conditions:

```cpp
#ifdef _WIN32
    // Windows-specific code
#else
    // Linux-specific code
#endif
```

This allows the same project to use the appropriate socket functions on each platform.

## 2. Current Server Flow

The current NullMesh server follows this flow:

```text
Initialize Winsock (Windows only)
             |
             v
       Create Socket
             |
             v
       Configure Address
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
        Receive Data
             |
             v
        Display Data
             |
             v
        Send Response
             |
             v
       Close Client Socket
             |
             v
      Close Server Socket
             |
             v
   Cleanup Winsock (Windows only)
```

## 3. Current Communication Example

The client sends:

```text
Hello NullMesh!
```

The server receives and displays:

```text
Client says: Hello NullMesh!
```

The server responds:

```text
Message received by NullMesh!
```

## 4. Current Implementation Limitations

The current implementation is a basic learning TCP server.

Its limitations include:

- It accepts one client connection and then finishes.
- It performs one receive operation.
- It sends one response.
- It does not yet handle partial sends in a loop.
- It does not implement message framing.
- It uses blocking socket operations.
- It does not yet support concurrent clients.

These are important distinctions when describing the current implementation. TCP itself supports multiple connections, but this particular server does not yet manage multiple clients.

---

# Part 9: Important Definitions

| Term | Simple Definition |
|---|---|
| Server | A program that provides a service to other programs. |
| Client | A program that requests a service from a server. |
| Network | Connected devices that can communicate with each other. |
| IP Address | An address used to identify a network interface. |
| Port | A number used to identify a communication endpoint. |
| Socket | A communication endpoint provided by the operating system. |
| TCP | A protocol that provides reliable and ordered data communication. |
| TCP Connection | An established communication relationship between two TCP endpoints. |
| Winsock | The Windows interface for socket programming. |
| POSIX Sockets | The socket programming interface used on Linux and other Unix-like systems. |
| SOCKET | The Windows data type used to identify a socket. |
| File Descriptor | A number used by Unix-like systems to identify an open resource. |
| Byte Stream | A continuous flow of bytes. |
| Listening Socket | A socket that waits for incoming client connections. |
| Connected Socket | A socket used to communicate with a connected client. |
| Three-Way Handshake | The three-step process TCP uses to establish a connection. |
| Backlog | The requested queue size for incoming connections waiting to be accepted. |
| Loopback Address | An IP address used to communicate with the same computer. |
| Blocking Operation | An operation that waits until it can make progress, completes, or fails. |
| Network Byte Order | The standard byte order used for values transmitted over a network. |
| `htons()` | Converts a 16-bit value from host byte order to network byte order. |
| `bind()` | Assigns a local address and port to a socket. |
| `listen()` | Prepares a socket to receive incoming connection requests. |
| `accept()` | Accepts an incoming connection and returns a new connected socket. |
| `recv()` | Receives data from a connected socket. |
| `send()` | Sends data through a connected socket. |
| `closesocket()` | Closes a Windows socket. |
| `close()` | Closes a Linux file descriptor, including a socket. |
| `WSAStartup()` | Initializes Winsock on Windows. |
| `WSACleanup()` | Cleans up Winsock on Windows. |
