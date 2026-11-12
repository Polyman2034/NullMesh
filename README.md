# NullMesh

A from-scratch C++ TCP and HTTP server built to explore networking, systems programming, and the foundations of web servers.

## About

NullMesh is a systems programming project developed from scratch in C++ to understand how network servers work at a lower level.

Instead of relying on high-level networking frameworks, the project focuses on implementing core networking concepts using operating-system socket APIs.

The development follows a practical learning approach:

**Understand → Design → Implement → Test → Improve**

## Current Stage

### Stage 1 — TCP Server

The basic TCP server has been implemented using C++17 and CMake.

**Implemented features:**

- TCP socket creation
- Binding to an IP address and port
- Listening for incoming connections
- Accepting a client connection
- Receiving data from a client
- Sending a response back to the client
- Socket cleanup and resource management
- Cross-platform socket handling for Windows and Linux

**Networking APIs used:**

| Function | Purpose |
|---|---|
| `socket()` | Creates a socket |
| `bind()` | Assigns an address and port |
| `listen()` | Waits for incoming connections |
| `accept()` | Accepts a client connection |
| `recv()` | Receives client data |
| `send()` | Sends data to the client |

**Current configuration:**

- Language: C++17
- Build system: CMake
- Protocol: TCP
- Port: `8080`
- Tested environment: GitHub Codespaces (Linux)
- Client testing: Python socket client

**Current limitation:** The server handles one client connection and one receive/send operation before shutting down. Multiple-client handling and reliable data transmission are planned improvements.

## Planned Stages

### Stage 1 — TCP Server
Build and strengthen the foundational TCP server.

### Stage 2 — HTTP Server
Implement HTTP request parsing, response generation, and HTTP handling on top of TCP.

### Stage 3 — Advanced HTTP Server
Explore concurrency, performance, connection management, and advanced server architecture.

## Building and Running

### Requirements

- C++17 compatible compiler
- CMake 3.20 or newer
- Git

### Build

Clone the repository:

```bash
git clone https://github.com/Polyman2034/NullMesh.git
cd NullMesh
```

Configure the project:

```bash
cmake -S . -B build
```

Compile:

```bash
cmake --build build
```

### Run

On Linux:

```bash
./build/NullMesh
```

On Windows with a Visual Studio CMake build:

```powershell
.\build\Debug\NullMesh.exe
```

### Test with a Python Client

Start the server first. In another terminal, run:

```bash
python3 -c 'import socket; s=socket.create_connection(("127.0.0.1", 8080)); s.sendall(b"Hello NullMesh!"); print(s.recv(1024).decode()); s.close()'
```

Expected response:

```text
Message received by NullMesh!
```

The server prints the received client message in its terminal.

## Project Structure

```text
NullMesh/
├── src/
│   └── main.cpp
├── include/
├── tests/
├── docs/
│   ├── architecture.md
│   ├── experiments.md
│   └── learning-notes.md
├── CMakeLists.txt
├── README.md
├── .gitignore
└── LICENSE
```

## Learning Philosophy

> WHY → HOW → CODE

Understand the problem first, explore how the underlying system solves it, and then implement it from scratch.

## Project Goals

- Understand networking at the socket level.
- Learn how TCP and HTTP servers work internally.
- Develop practical systems programming skills in C++.
- Explore cross-platform networking.
- Build a server without depending on high-level frameworks.

---

<p align="center">
  <i>Learn. Build. Experiment. Improve.</i> 🚀
</p>
