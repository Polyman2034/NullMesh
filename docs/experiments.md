# NullMesh — Experiments

This document records practical experiments performed while building and understanding the NullMesh TCP server.

Each experiment describes its objective, setup, procedure, expected behavior, and actual observations.

---

# Experiment 1: TCP Communication Between Two Terminals

## Objective

Understand how two programs communicate using a TCP connection.

## Tools

- Two terminal windows.
- TCP client and server programs.
- Python socket module.

## Setup

A basic TCP communication experiment was performed using two terminals.

The first terminal runs the server, while the second terminal runs a Python client.

## Procedure

1. Start the TCP server.
2. Connect to the server using a Python socket client.
3. Send a message from the client.
4. Observe the message received by the server.
5. Observe the response received by the client.

## Test Command

```bash
python3 -c 'import socket; s=socket.create_connection(("127.0.0.1", 8080)); s.sendall(b"Hello NullMesh!"); print(s.recv(1024).decode()); s.close()'
```

## Expected Behavior

- The client establishes a TCP connection with the server.
- The client sends a message.
- The server receives and displays the message.
- The server sends a response.
- The client receives the response.

## Actual Observations

The experiment was successfully performed in GitHub Codespaces on Linux.

Client message:

```text
Hello NullMesh!
```

Server output:

```text
TCP socket created successfully!
Socket bound to port 8080!
Server is listening on port 8080!
Client connected successfully!
Client says: Hello NullMesh!
Response sent to client!
```

Client response:

```text
Message received by NullMesh!
```

## Conclusion

This experiment demonstrated successful TCP communication between two separate programs running on the same computer.

---

# Experiment 2: TCP Socket Creation

## Objective

Understand how a C++ application creates a TCP socket using the operating system's socket API.

## Functions Used

**Windows:**

```cpp
WSAStartup();
socket();
closesocket();
WSACleanup();
```

**Linux:**

```cpp
socket();
close();
```

## Procedure

1. Initialize Winsock on Windows.
2. Create a TCP socket using `socket()`.
3. Check whether the returned socket is valid.
4. Print a success or error message.
5. Close the socket when finished.
6. Clean up Winsock resources on Windows.

## Actual Observations

The complete TCP server successfully created a socket in the Linux Codespaces environment.

Output:

```text
TCP socket created successfully!
```

## Conclusion

This experiment demonstrated how an application requests a TCP socket from the operating system.

---

# Experiment 3: Binding a Socket to a Port

## Objective

Understand how a server assigns a local IP address and port to a socket.

## Functions Used

```cpp
socket();
bind();
```

## Configuration

```text
Address Family: IPv4
IP Address:     INADDR_ANY
Port:           8080
```

## Procedure

1. Create a TCP socket.
2. Configure the IPv4 address structure.
3. Set the port using `htons()`.
4. Call `bind()`.
5. Check the return value.

## Actual Observations

The server successfully bound its socket to port `8080`.

Output:

```text
Socket bound to port 8080!
```

## Conclusion

This experiment demonstrated how a server associates its socket with a local address and port.

---

# Experiment 4: Listening for Connections

## Objective

Understand how a TCP socket is prepared to accept incoming client connections.

## Functions Used

```cpp
bind();
listen();
```

## Procedure

1. Create and bind a TCP socket.
2. Call `listen()`.
3. Check whether the operation succeeded.
4. Attempt to connect using a TCP client.

## Actual Observations

The server successfully entered listening mode.

Output:

```text
Server is listening on port 8080!
```

The server waited for a client connection before continuing to the `accept()` operation.

## Conclusion

This experiment demonstrated the difference between assigning a local address and preparing a socket to listen for connections.

---

# Experiment 5: Accepting a Client Connection

## Objective

Understand how a server accepts a client's TCP connection.

## Functions Used

```cpp
listen();
accept();
```

## Procedure

1. Start the TCP server.
2. Allow it to reach the blocking `accept()` operation.
3. Connect using the Python client.
4. Observe when `accept()` returns.

## Actual Observations

The server successfully accepted the Python client's connection.

Output:

```text
Client connected successfully!
```

The server used the newly returned client socket for communication.

## Conclusion

This experiment demonstrated how a server accepts a client connection and obtains a separate socket for communication.

---

# Experiment 6: Receiving Data from a Client

## Objective

Understand how a server receives data sent by a connected client.

## Functions Used

```cpp
accept();
recv();
```

## Procedure

1. Start the TCP server.
2. Connect a client.
3. Call `recv()` on the connected client socket.
4. Send text from the client.
5. Display the received data.

## Actual Observations

The Python client sent:

```text
Hello NullMesh!
```

The server displayed:

```text
Client says: Hello NullMesh!
```

The server successfully received and displayed the client's message.

## Conclusion

This experiment demonstrated how the server receives bytes through a connected TCP socket.

---

# Experiment 7: Sending Data to a Client

## Objective

Understand how a server sends data to a connected client.

## Functions Used

```cpp
send();
```

## Procedure

1. Start the TCP server.
2. Connect a client.
3. Prepare a response message.
4. Send the response using the connected client socket.
5. Observe the received message in the client terminal.

## Actual Observations

The server sent:

```text
Message received by NullMesh!
```

The client successfully received and displayed the response.

Server output:

```text
Response sent to client!
```

## Conclusion

This experiment demonstrated successful data transmission from the server to the client.

---

# Experiment 8: Closing a TCP Connection

## Objective

Understand how sockets are closed after communication.

## Functions Used

**Windows:**

```cpp
closesocket();
WSACleanup();
```

**Linux:**

```cpp
close();
```

## Procedure

1. Start the TCP server.
2. Connect a client.
3. Exchange data.
4. Close the client socket.
5. Close the server's client socket and listening socket.
6. Perform platform-specific cleanup.

## Actual Observations

The Python client completed its communication and closed its socket.

The server closed its client socket and listening socket after processing the connection.

The server process then exited.

## Conclusion

This experiment demonstrated socket cleanup after a completed client-server exchange.

---

# Experiment 9: Complete TCP Server Test

## Objective

Test the complete TCP server lifecycle from socket creation to communication and cleanup.

## Procedure

1. Initialize Winsock on Windows, if applicable.
2. Create the server socket.
3. Bind it to an IPv4 address and port.
4. Start listening.
5. Accept a client connection.
6. Receive data from the client.
7. Process the received data.
8. Send a response.
9. Close the connected socket.
10. Close the listening socket.
11. Clean up platform-specific resources.

## Actual Observations

The complete server was successfully compiled and tested in GitHub Codespaces on Linux.

Client-to-server communication and server-to-client response transmission both worked successfully.

The server handled one client connection and then exited.

## Conclusion

This experiment verified the basic TCP server lifecycle, including socket creation, binding, listening, accepting, receiving, sending, and cleanup.

---

# Experiment 10: Cross-Platform Build Configuration

## Objective

Prepare NullMesh to use the appropriate socket API on Windows and Linux.

## Technologies Used

- C++17
- CMake
- Winsock
- POSIX sockets

## Implementation

Platform-specific code is selected using the `_WIN32` preprocessor definition.

Windows uses Winsock, while Linux uses POSIX socket headers and functions.

CMake links the Windows Winsock library using:

```cmake
if(WIN32)
    target_link_libraries(NullMesh PRIVATE ws2_32)
endif()
```

## Actual Observations

The cross-platform implementation successfully compiled in GitHub Codespaces on Linux.

Build command:

```bash
cmake -S . -B build
cmake --build build
```

Result:

```text
[100%] Built target NullMesh
```

The Windows version previously compiled, but execution of the locally built executable was blocked by Windows Smart App Control. The new cross-platform implementation has not yet been independently verified through a successful Windows runtime test.

## Conclusion

This experiment established a cross-platform socket abstraction for Windows and Linux, with successful Linux compilation and runtime testing.

---

# Experiment Results

| Experiment | Actual Result |
|---|---|
| TCP communication between terminals | Successful using Python client |
| Socket creation | Successful on Linux |
| Binding to port 8080 | Successful |
| Listening for connections | Successful |
| Accepting a client | Successful |
| Receiving client data | Successful |
| Sending server response | Successful |
| Closing a connection | Completed successfully |
| Complete TCP server test | Successful on Linux |
| Cross-platform build configuration | Linux build successful; Windows runtime verification pending |

---

# Technical Observations

- `socket()` creates the communication endpoint.
- `bind()` associates the server socket with a local address and port.
- `listen()` prepares the socket to accept incoming connections.
- Blocking `accept()` waits until a client connects.
- `accept()` returns a new socket for communication with the connected client.
- `recv()` receives bytes from the TCP connection.
- `send()` transmits bytes through the connected socket.
- TCP is a byte stream and does not automatically preserve application message boundaries.
- A successful `send()` does not necessarily mean that the entire message was sent.
- Windows and Linux use different socket cleanup functions and error-reporting mechanisms.
- The current implementation handles one client connection before shutting down.
