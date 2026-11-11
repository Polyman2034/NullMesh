# NullMesh — Experiments

This document records practical experiments performed while building and understanding the NullMesh TCP server.

Each experiment includes its objective, setup, procedure, expected behavior, and observations.

---

# Experiment 1: TCP Communication Between Two Terminals

## Objective

Understand how two programs communicate using a TCP connection.

## Tools

- Two terminal windows.
- Netcat (`nc`) or Ncat (`ncat`).

## Setup

Start a listener in Terminal 1:

```bash
ncat -l 8080
```

Connect to it from Terminal 2:

```bash
ncat 127.0.0.1 8080
```

If using a different Netcat version, the listener command may have different syntax.

## Procedure

1. Start the listener in the first terminal.
2. Connect to port `8080` from the second terminal.
3. Type a message in either terminal.
4. Observe the message in the other terminal.
5. Close one side and observe what happens.

## Expected Behavior

- The second terminal establishes a TCP connection with the first.
- Text entered in one terminal is received by the other.
- Closing the connection ends communication.

## Observations

Record the actual output and behavior after running the experiment.

## Conclusion

This experiment demonstrates basic TCP communication between two programs running on the same computer.

---

# Experiment 2: TCP Socket Creation

## Objective

Understand how a C++ application creates a TCP socket using Winsock.

## Functions Used

```cpp
WSAStartup();
socket();
closesocket();
WSACleanup();
```

## Procedure

1. Initialize Winsock.
2. Create a socket using `socket()`.
3. Check whether the returned socket is valid.
4. Print a success or error message.
5. Close the socket.
6. Clean up Winsock.

## Expected Behavior

If Winsock initializes successfully and the socket is created successfully, the program should print a success message.

## Observations

Record:

- Whether `WSAStartup()` succeeded.
- Whether `socket()` returned a valid socket.
- Any error codes.
- Whether cleanup completed successfully.

## Conclusion

This experiment demonstrates how an application requests a socket resource from the operating system.

---

# Experiment 3: Binding a Socket to a Port

## Objective

Understand how a server assigns a local IP address and port to a socket.

## Functions Used

```cpp
socket();
bind();
closesocket();
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

## Expected Behavior

If the address and port are available and the operation succeeds, the socket becomes associated with that local address and port.

If the port is already in use or another error occurs, binding may fail.

## Observations

Record:

- Whether `bind()` succeeded.
- The port used.
- Any error code.
- What happens when another program tries to bind to the same address and port.

## Conclusion

This experiment demonstrates how a server chooses the local address and port on which it will communicate.

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

1. Create a TCP socket.
2. Bind it to port `8080`.
3. Call `listen()`.
4. Check whether the operation succeeded.
5. Attempt to connect using a TCP client.

## Expected Behavior

The socket enters listening mode and becomes ready to accept incoming TCP connections.

`listen()` itself does not accept a client.

## Observations

Record:

- Whether `listen()` succeeded.
- Whether a client could establish a connection.
- What happened when no client was connected.

## Conclusion

This experiment demonstrates the difference between assigning a local address and preparing a socket to listen for connections.

---

# Experiment 5: Accepting a Client Connection

## Objective

Understand how a server accepts a client's connection.

## Functions Used

```cpp
listen();
accept();
```

## Procedure

1. Create and bind a TCP socket.
2. Put it into listening mode.
3. Call `accept()`.
4. Connect a client to the server.
5. Observe when `accept()` returns.

## Expected Behavior

Before a client connects, a blocking `accept()` waits.

When a client connects, `accept()` returns a new connected socket.

The original listening socket remains available to accept other clients.

## Observations

Record:

- Whether `accept()` waited for a client.
- When it returned.
- Whether a valid client socket was created.
- The difference between the listening socket and client socket.

## Conclusion

This experiment demonstrates how a server accepts client connections and obtains a separate socket for communication.

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
4. Send some text from the client.
5. Display the received bytes.

## Expected Behavior

The server receives available data and stores it in the supplied buffer.

The return value tells the server how many bytes were received.

## Important Return Values

| Return Value | Meaning |
|---|---|
| Positive number | Number of bytes received. |
| `0` | The peer has gracefully closed its sending direction. |
| `SOCKET_ERROR` | The receive operation failed. |

## Observations

Record:

- The message sent by the client.
- The number of bytes received.
- What happened when the client sent a larger message.
- What happened when the client disconnected.

## Conclusion

This experiment demonstrates how the server receives bytes through a connected TCP socket.

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
4. Call `send()` using the connected client socket.
5. Observe the received message in the client terminal.

## Expected Behavior

The server passes data to Winsock for sending through the TCP connection.

The return value indicates how many bytes were accepted for sending.

## Observations

Record:

- The message sent by the server.
- The number of bytes reported by `send()`.
- Whether the client received the message.
- What happens when the connection is closed.

## Conclusion

This experiment demonstrates how a server sends data to a connected client.

---

# Experiment 8: Closing a TCP Connection

## Objective

Understand what happens when a TCP connection is closed.

## Functions Used

```cpp
closesocket();
WSACleanup();
```

## Procedure

1. Start the TCP server.
2. Connect a client.
3. Exchange some data.
4. Close the connected socket.
5. Observe the behavior of the other endpoint.
6. Close the listening socket and clean up Winsock.

## Expected Behavior

Closing a socket releases its associated resources.

The other endpoint may detect that the peer has closed its sending direction when it calls `recv()` and receives `0`.

## Observations

Record:

- Which endpoint closed first.
- What the other endpoint observed.
- Whether `recv()` returned `0` or an error.
- Whether the server could accept another client.

## Conclusion

This experiment demonstrates connection closing and socket resource cleanup.

---

# Experiment 9: Complete TCP Server Test

## Objective

Test the complete TCP server lifecycle from socket creation to communication and cleanup.

## Procedure

1. Initialize Winsock.
2. Create the server socket.
3. Bind it to an IPv4 address and port.
4. Start listening.
5. Accept a client connection.
6. Receive data from the client.
7. Process the received data.
8. Send a response.
9. Close the connected socket.
10. Close the listening socket.
11. Clean up Winsock.

## Expected Communication

```text
Client                         NullMesh Server
   |                                  |
   |---------- Connect -------------->|
   |                                  |
   |---------- Message -------------->|
   |                                  |
   |<--------- Response --------------|
   |                                  |
   |---------- Disconnect ----------->|
   |                                  |
   |           Connection Closed      |
```

## Observations

Record:

- Whether the server started successfully.
- Whether the client connected.
- Whether data was received correctly.
- Whether the response reached the client.
- Whether sockets were closed correctly.
- Any errors encountered.

## Conclusion

This experiment tests the complete basic TCP server communication process.

---

# Experiment Results

Use this section to record actual results after running the experiments.

| Experiment | Actual Result |
|---|---|
| TCP communication between terminals | Record observation |
| Socket creation | Record observation |
| Binding to a port | Record observation |
| Listening for connections | Record observation |
| Accepting a client | Record observation |
| Receiving client data | Record observation |
| Sending server data | Record observation |
| Closing a connection | Record observation |
| Complete TCP server test | Record observation |

---

# Technical Observations

Use this section to record unexpected behavior, errors, debugging findings, and important discoveries made during the experiments.

Examples of useful observations:

- Why a particular Winsock function failed.
- What happened when a port was already in use.
- Why `accept()` waited before a client connected.
- Why `recv()` returned fewer bytes than expected.
- What happened when a client disconnected.
- Differences between the listening socket and connected socket.

These observations should describe what actually happened during testing.
