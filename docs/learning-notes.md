# NullMesh — Networking Learning Notes

> **Project:** NullMesh
> **Stage:** Stage 1 — TCP Server
> **Goal:** Understand networking fundamentals before implementing the server.

---

# Networking Fundamentals

## 1. What is a server?

### My Understanding

A server is a **program/process running on a computer** that:

1. Listens for requests from clients.
2. Processes those requests.
3. Sends a response back.

### Mental Model

```text
Client → Request → Server
Client ← Response ← Server
```

### Key Idea

A server is primarily the **software/program providing a service**, not necessarily a separate physical computer.

---

## 2. How does a client communicate with a server?

### My Understanding

For a basic client-server model:

```text
Client
   ↓
Network
   ↓
Server
   ↓
Response
   ↓
Client
```

In real-world web applications, there can be additional components:

```text
Client
  ↓
DNS
  ↓
Reverse Proxy
  ↓
API Gateway
  ↓
Server
```

However, NullMesh Stage 1 focuses on the basic:

```text
Client ↔ Server
```

communication model.

### Key Idea

A client sends a request through a network to a server, and the server processes the request and sends a response.

---

## 3. What is a network connection?

### Important Distinction

A **network** is the overall system that allows devices to communicate.

A **network connection** is an established communication link between two endpoints.

### Network

```text
Computer A ─── Computer B ─── Computer C
```

### Network Connection

```text
Computer A ═══════════ Computer B
             ↑
       communication
```

### NullMesh Mental Model

```text
Client
   │
   │ TCP connection
   ▼
NullMesh Server
```

### Key Idea

A network is the overall communication environment.

A network connection is the communication link established between two endpoints.

---

## 4. How does the system identify where network data should go?

### Mental Model

Think about the combination:

```text
IP address + Port
```

The IP address helps identify **which machine/network endpoint** to reach.

The port identifies **which network service/endpoint** on that machine.

### Example

```text
192.168.1.10:8080
      │       │
      │       └── Port
      └────────── IP address
```

### Key Idea

```text
IP address → Which machine?
Port       → Which network service?
```

---

## 5. What is a port, and why do we need it?

### Answer

A port is a **number used to identify a particular network service/endpoint on a computer**.

### Mental Model

```text
IP address → Which machine?
Port       → Which network service?
```

### Example

```text
192.168.1.10:8080
```

This means roughly:

> Reach the machine identified by `192.168.1.10`, using the service associated with port `8080`.

### Important

A port is **not a physical/network path**.

It is a numbered network endpoint used to distinguish services.

---

## 6. What is a socket?

### Answer

A socket is a **communication endpoint provided/managed by the operating system that a program uses to send and receive network data**.

### Mental Model

```text
C++ Program
     ↓
   Socket
     ↓
Operating System
     ↓
   Network
```

### Key Idea

The socket is the program's interface/endpoint for network communication.

---

## 7. What is a file descriptor?

### Status

**Not fully learned yet.**

### Current Understanding

On Unix/Linux, a socket is commonly referred to by a **file descriptor**, which is an identifier such as:

```text
4
```

However, NullMesh is currently being developed on Windows.

Windows networking uses a `SOCKET` handle rather than treating sockets exactly like Unix file descriptors.

### Key Idea

Do not assume:

```text
Socket = File Descriptor
```

They are related, but the exact mechanism depends on the operating system.

### To Learn Later

Understand:

* What an OS handle/identifier is
* How the OS keeps track of resources
* Unix file descriptors
* Windows `SOCKET` handles

---

## 8. What is TCP, and why do we need it?

### Answer

**TCP = Transmission Control Protocol.**

TCP is a **communication protocol that allows two endpoints to communicate reliably and in an ordered way**.

### Mental Model

```text
Client
   │
   │ TCP
   ▼
Server
```

### TCP Provides Mechanisms For

* Reliable delivery
* Ordered data
* Detecting problems with transmitted data
* Flow control

### Important

TCP does **not** mean:

> "Connect the computer to the internet."

Wi-Fi/Ethernet/network connectivity provides access to the network.

TCP defines **how two endpoints communicate reliably over that network**.

---

# 9. What does `socket()` do?

### Status

**Not answered yet.**

### Hint

The C++ program needs to ask the operating system for a socket.

```text
Your C++ Program
       │
       │ socket()
       ▼
Operating System
       │
       │ creates/provides
       ▼
    Socket
```

### Question

> What does `socket()` do?

---

# Current Mental Picture

```text
                    NETWORK
                       │
          ┌────────────┴────────────┐
          │                         │
       CLIENT                    SERVER
          │                         │
          │                         │
          └────── TCP connection ───┘
                         │
                       Socket
                         │
                    C++ Program
```

---

# Addressing Mental Model

```text
IP address
     ↓
Which machine?
```

```text
Port
     ↓
Which network service?
```

```text
Socket
     ↓
Communication endpoint used by the program
```

```text
TCP
     ↓
Rules/protocol for reliable,
ordered communication
```

---

# TCP Server Lifecycle — Preview

Eventually, NullMesh Stage 1 will involve:

```text
socket()
   ↓
bind()
   ↓
listen()
   ↓
accept()
   ↓
recv()
   ↓
send()
   ↓
close()
```

This sequence is only a **preview**.

Each function will be understood separately:

1. What problem does it solve?
2. Why do we need it?
3. What is its purpose?
4. What exactly is it?
5. How does it work?
6. When and why do we use it?
7. Can I explain and apply it myself?

---

# Learning Rule

For NullMesh:

> **WHY → HOW → CODE**

Do not memorize networking functions.

First understand the problem.

Then understand the concept.

Then understand how the OS solves it.

Only then write the code.

---

# Project Learning Flow

```text
Problem
   ↓
Why do we need it?
   ↓
Purpose
   ↓
What exactly is it?
   ↓
How does it work?
   ↓
How will we implement it?
   ↓
Implement
   ↓
Test
   ↓
Experiment
   ↓
Measure
   ↓
Analyze
   ↓
Improve
```

---

# Current Progress

* [x] What is a server?
* [x] Client-server communication
* [x] Network vs network connection
* [x] IP address
* [x] Port
* [x] Socket
* [ ] File descriptor / Windows socket handle
* [x] TCP basics
* [ ] `socket()`
* [ ] `bind()`
* [ ] `listen()`
* [ ] `accept()`
* [ ] `recv()`
* [ ] `send()`
* [ ] `close()` / `closesocket()`

---

<p align="center">
  <i>“Learn. Build. Experiment. Improve.”</i> 🚀
</p>

