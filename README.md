# final-project-group-3

Project: Implement a peer-to-peer Raft chat application

Why?
 Provide a distributed chat application that is more durable and private. Raft provides a decentralized way for having consistent data across devices/users that can handle crash faults.
How? 
Building off an existing Raft implementation (NuRaft).

# Instructions

Build NuRaft (see below)

Change directory to NuRaft/build/examples.

run echo_server as follows:

./echo_server [server number] [IP Address]

For testing on localhost, can type "./echo_server 1 localhost:10001" etc.

Will be greeted by prompt.

To add other servers to cluster, type "add [server number] [IP Address]"

To send message type "msg [message text]"

To leave chat, type "leave"

# NuRaft

Raft implementation derived from the [cornerstone](https://github.com/datatechnology/cornerstone) project, which is a very lightweight C++ implementation with minimum dependencies, originally written by [Andy Chen](https://github.com/andy-yx-chen).

New features that are not described in the [original paper](https://raft.github.io/raft.pdf), but required for the real-world use cases in eBay, have been added. NuRaft authors believe those features are useful for others outside eBay as well.

How to Build
------------
#### 1. Install `cmake` and `openssl`: ####

* Ubuntu
```sh
$ sudo apt-get install cmake
$ sudo apt-get install openssl libssl-dev
```

* OSX
```sh
$ brew install cmake
$ brew install openssl
```
* Windows
    * Download and install [CMake](https://cmake.org/download/).
    * Currently, we do not support SSL for Windows.

#### 2. Fetch [Asio](https://github.com/chriskohlhoff/asio) library: ####

* Linux & OSX
```sh
$ ./prepare.sh
```
* Windows
    * Clone [Asio](https://github.com/chriskohlhoff/asio) into the project directory.

#### 3. Build static library, tests, and examples: ####

* Linux & OSX
```sh
$ mkdir build
$ cd build
build$ cmake ../
build$ make
```

Run unit tests
```sh
build$ ./runtests.sh
```

* Windows:
```sh
C:\NuRaft> mkdir build
C:\NuRaft> cd build
C:\NuRaft\build> cmake -G "NMake Makefiles" ..\
C:\NuRaft\build> nmake
```

You may need to run `vcvars` script first in your `build` directory. For example (it depends on how you installed MSVC):
```sh
C:\NuRaft\build> c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat
```

