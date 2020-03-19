# Raft Chat

A peer-to-peer Raft chat application that provides a more durable and private platform during disaster scenarios. 
By utilizing the Raft concensus protocol, we have a decentralized way for having consistent chat messages
across devices/users that can handle crash faults. NuRaft, a lightweight C++ Raft library
written by Gene Zhang and Jung-Sang Ahn of eBay, was used as a foundation. (The authors based their work on prior work
by Andy Chen)

## Code Structure
    .
    ├── NuRaft 
    |   ├── examples 
    |   │   ├── central_server.hxx           # Central Server API Header
    |   │   ├── central_server.cxx           # Central Server API Implementation
    |   │   ├── central_server_common.hxx    # Contains shared CS functions & variables
    |   │   ├── example_common.hxx           # Helper functions and main user interface loop
    |   │   ├── echo
    |   |   │   ├── echo_server.cxx          # Entry point for app
    |   |   │   ├── echo_state_machine.hxx   # Modified for evaluations
    |   |   |   └── ... 
    |   │   └── ...
    |   ├── include 
    |   │   ├── libnuraft                    # Controls forwarding from follower to leaders
    |   │   └── ...
    |   ├── blocking_tcp_echo_server.cpp     # Central Server program
    |   └── ...
    └── ...

The Raft Chat project is comprised of the `chat app` and the `central server`. All related
files currently reside in the NuRaft folder. (*those related to the app are under examples and include,
while the central server file is at the base*)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine and/or remote
servers for development and testing purposes.

### Prerequisites

The following dependencies are required:

```
  build-essential \
  zlib1g          \
  zlib1g-dev      \
  cmake           \
  openssl         \
  libssl-dev 
```

### Installation 

You must first install [NuRaft](./NuRaft/README.md)

Then you must build the central server code:
```
  cd NuRaft
  make asio_server
```

### Deployment

To run a lobby of clients, you must run this on seperate machines:
```
  cd NuRaft/build/examples
  ./echo_server [server number] [IP Address]:[port number]
```

Then you want to run the central server:
```
  cd NuRaft
  ./asio_server [port number]
```

This allows for auto joining between clients and lobbies

For testing on localhost, can type in separate terminal windows: 
```
./echo_server 1 localhost:10001  
./echo_server 2 localhost:10002
```

You will then be greeted by a prompt. As this is run locally, the central server
will not be active. To add other clients to the lobby, type:
```
add [server number] [IP Address]
```

Server that adds others is initial leader (only leader can add).

To send message type: 
```
msg [message text]
```

To leave chat, type: 
```
leave
```
