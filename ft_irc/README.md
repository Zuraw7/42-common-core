# ft_irc
A simple IRC server implementation in C++98

# About
``ft_irc`` is a basic implementation of an Internet Relay Chat (IRC) server. The goal is to replicate core IRC protocol features using C++98, non-blocking sockets, and the ``poll()`` system call. This project focuses on real-time, text-based communication over TCP, following the IRC RFC standards as closely as possible within the project scope.

# Features
- Handle multiple client connections simultaneously using **non-blocking I/O**
- Use of **poll()** for all file descriptor events (read, write, listen)
- Support for real-time messaging (public and private)
- Channel support with message broadcasting
- User authentication with password
- Role management:
- Regular users
- Channel operators
- Implementation of key IRC commands:
	- ``NICK``, ``USER``, ``JOIN``, ``PART``, ``PRIVMSG``, ``QUIT``
- Operator commands: ``KICK``, ``INVITE``, ``TOPIC``, ``MODE``
	- ``i``: invite-only
	- ``t``: topic set by operators only
	- ``k``: channel password
	- ``o``: give/take operator status
	- ``l``: user limit

# Technologies
- **C++98**
- **poll()** system call
- **TCP/IP (IPv4)**
- POSIX sockets

# How to run
Download project:
`` git clone https://github.com/Zuraw7/42-common-core.git``

Enter repository:
``cd ft_irc``

Create an executable with Makefile:
``make``

Run the server:
``./ircserv <port> <password>`` for example ``./ircserv 6667 secretpass``

Join the server:
- Using terminal ``nc localhost <port>`` for example ``nc localhost 6667``
- Using halloy with this settings:
```bash
[servers.local]
password = "pass"
nickname = "user1"
server = "127.0.0.1"
port = 6667
channels = ["#42", "#halloy"]
use_tls = false

[servers.local1]
password = "pass"
nickname = "user2"
server = "127.0.0.1"
port = 6667
channels = ["#42", "#halloy"]
use_tls = false
```
