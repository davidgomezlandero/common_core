# ft_irc

## Table of Contents
1. [Overview](#overview)
2. [Authors](#authors)
3. [Usage](#usage)
4. [Supported Commands](#supported-commands)
5. [How It Works](#how-it-works)
6. [Project Structure](#project-structure)
7. [Key Data Structures](#key-data-structures)
8. [Implementation Details](#implementation-details)
   - [Server Startup](#server-startup)
   - [poll() Loop](#poll-loop)
   - [Client Registration](#client-registration)
   - [Command Parsing and Dispatch](#command-parsing-and-dispatch)
   - [Channel Management](#channel-management)
   - [Channel Modes](#channel-modes)
   - [Operator Privileges](#operator-privileges)
   - [IRC Numeric Replies](#irc-numeric-replies)
   - [Error Handling](#error-handling)
9. [Build](#build)
10. [Testing](#testing)

---

## Overview

ft_irc is a fully functional IRC server written in **C++98**. It handles
multiple simultaneous clients over TCP/IP using a single non-blocking `poll()`
loop — no threads, no `fork()`. Clients connect with any standard IRC client
(tested with `irssi` and raw `nc`).

---

## Authors

| Developer | GitHub | Responsibility |
|-----------|--------|----------------|
| **davigome** | [davidgomezlandero](https://github.com/davidgomezlandero) | `Server` class, `poll()` loop, client lifecycle, `Channel` class, `MODE`, `KICK`, `INVITE`, `TOPIC` |
| **Jeferson Sopan** | [JefersonSopanR](https://github.com/JefersonSopanR) | `PASS`, `NICK`, `USER`, `JOIN`, `PART`, `PRIVMSG`, `QUIT`, `PING`, numeric replies, `fillmessage` |

---

## Usage

```bash
make
./ircserv <port> <password>

# Example
./ircserv 6667 mypassword
```

Connect with `irssi`:

```bash
irssi
/connect localhost 6667 mypassword
/nick mynick
/join #general
/msg #general Hello world
```

Connect with `nc` (raw testing):

```bash
nc localhost 6667
PASS mypassword
NICK mynick
USER myuser 0 * :Real Name
JOIN #general
PRIVMSG #general :hello
```

---

## Supported Commands

These are the commands actually implemented in the codebase:

### Registration

| Command | Syntax | Description |
|---------|--------|-------------|
| `PASS` | `PASS <password>` | Authenticate with the server password — must be sent before NICK and USER |
| `NICK` | `NICK <nickname>` | Set or change nickname — checked for uniqueness across all connected clients |
| `USER` | `USER <username> 0 * :<realname>` | Set username and real name — completes the registration handshake |

### Channels

| Command | Syntax | Description |
|---------|--------|-------------|
| `JOIN` | `JOIN <#channel>` | Join a channel, creating it if it does not exist. First joiner becomes channel operator |
| `PART` | `PART <#channel> [:<message>]` | Leave a channel, notifying all remaining members |
| `PRIVMSG` | `PRIVMSG <#channel\|nick> :<message>` | Send a message to a channel or directly to a user |
| `TOPIC` | `TOPIC <#channel> [:<topic>]` | Get the current topic or set a new one (restricted by `+t` mode) |
| `INVITE` | `INVITE <nick> <#channel>` | Invite a user to a channel (required when channel is `+i`) |
| `KICK` | `KICK <#channel> <nick> [:<reason>]` | Remove a user from a channel (operator only) |
| `MODE` | `MODE <#channel> <+/-flag> [param]` | Set or unset channel modes (see below) |

### Connection

| Command | Syntax | Description |
|---------|--------|-------------|
| `PING` | `PING <token>` | Keepalive — server responds with `PONG <token>` |
| `QUIT` | `QUIT [:<message>]` | Disconnect cleanly, notifying all channels the user was in |

---

## How It Works

```
./ircserv <port> <password>
    │
    ├── Create TCP socket → setsockopt(SO_REUSEADDR) → bind → listen
    │
    ├── Add server fd to _pollfds vector
    │
    └── poll() loop:
            │
            ├── server fd POLLIN?
            │       └── accept() → new Client → push to _clients and _pollfds
            │
            ├── client fd POLLIN?
            │       ├── recv() into client _buffer
            │       ├── Extract complete messages split on \r\n
            │       └── parseAndExecute():
            │               ├── Split prefix / command / params
            │               └── Dispatch:
            │                       PASS   → check password, set _passOk
            │                       NICK   → validate, check uniqueness
            │                       USER   → set _userName/_realName
            │                           └── if PASS+NICK+USER done → send 001-004
            │                       JOIN   → find/create channel, add member
            │                       PART   → remove from channel, notify members
            │                       PRIVMSG→ route to channel or user fd
            │                       TOPIC  → get or set channel topic
            │                       INVITE → add to channel invite list
            │                       KICK   → remove target from channel
            │                       MODE   → apply +i +t +k +l +o flags
            │                       PING   → send PONG
            │                       QUIT   → part all channels, close fd
            │
            └── recv() == 0 or error?
                    └── client disconnected → part channels, erase from _pollfds/_clients
```

---

## Project Structure

```
ft_irc/
├── ircserv.hpp              # Global includes, defines, forward declarations
├── Server.hpp               # Server class declaration
├── Server.cpp               # Server — startup, poll() loop, dispatch, helpers
├── Client.hpp               # Client class declaration
├── Client.cpp               # Client — state, buffer, getters/setters
├── Channel.hpp              # Channel class declaration
├── Channel.cpp              # Channel — members, operators, invite list, modes
├── irc_messages.hpp         # IRC numeric reply string constants
├── fillmessage.cpp          # sendfillmessage() — builds and sends numeric replies
├── commands/
│   ├── pass.cpp             # PASS — password authentication
│   ├── nick.cpp             # NICK — nickname registration and change
│   ├── user.cpp             # USER — username/realname, triggers welcome sequence
│   ├── join.cpp             # JOIN — join or create channel
│   ├── part.cpp             # PART — leave channel
│   ├── privmsg.cpp          # PRIVMSG — message to channel or user
│   ├── topic.cpp            # TOPIC — get/set channel topic
│   ├── invite.cpp           # INVITE — add user to invite list
│   ├── kick.cpp             # KICK — remove user from channel
│   ├── mode.cpp             # MODE — channel mode flags
│   ├── ping.cpp             # PING — keepalive
│   └── quit.cpp             # QUIT — clean disconnection
└── Makefile
```

---

## Key Data Structures

```cpp
// One connected client
class Client
{
    private:
        int             _fd;
        std::string     _nickName;
        std::string     _userName;
        std::string     _realName;
        std::string     _buffer;       // partial recv buffer — holds incomplete IRC lines
        bool            _registered;   // true once PASS + NICK + USER all completed
        bool            _passOk;       // true once correct PASS received
        bool            _isOperator;   // true once OPER command succeeded
};

// One IRC channel
class Channel
{
    private:
        std::string              _channelName;
        std::string              _topic;
        std::string              _key;          // password set by +k mode
        std::vector<Client *>    _members;
        std::vector<Client *>    _operators;    // channel operators (@)
        std::vector<Client *>    _invited;      // invite list for +i mode
        bool                     _inviteOnly;   // +i flag
        bool                     _topicRestrict;// +t flag
        int                      _userLimit;    // 0 = no limit, >0 set by +l
};

// The server — owns all state
class Server
{
    private:
        int                      _fd;           // listening socket fd
        int                      _port;
        std::string              _password;
        std::string              name;           // server name string
        std::vector<pollfd>      _pollfds;       // watched by poll()
        std::vector<Client *>    _clients;
        std::vector<Channel *>   _channels;
};
```

---

## Implementation Details

### Server Startup

`Server::start()` in [`Server.cpp`](Server.cpp):

1. Creates a TCP socket with `socket(AF_INET, SOCK_STREAM, 0)`.
2. Sets `SO_REUSEADDR` so the port can be reused immediately after restart.
3. Sets the socket to non-blocking with `fcntl(fd, F_SETFL, O_NONBLOCK)`.
4. Binds to `0.0.0.0:<port>` and calls `listen()`.
5. Pushes the server fd as the first `pollfd` entry (`POLLIN`).

### poll() Loop

`Server::loop()` calls `poll(_pollfds.data(), _pollfds.size(), -1)` in an
infinite loop. Each ready fd is checked:

- **Server fd** → `accept()` the connection, allocate a `Client`, push its fd
  to `_pollfds` and the pointer to `_clients`.
- **Client fd** → `recv()` up to 512 bytes into the client's `_buffer`. The
  buffer is scanned for `\r\n`. Every complete line is extracted and passed
  to `parseAndExecute()`. If `recv()` returns 0 the client is cleaned up.

### Client Registration

Before any channel command is accepted a client must complete three steps in
order:

```
PASS <password>         →  checked against _password, sets _passOk
NICK <nickname>         →  uniqueness checked across _clients
USER <u> 0 * :<real>   →  sets _userName and _realName
                            _registered = true
                            Sends numeric welcome sequence:
                                001 RPL_WELCOME
                                002 RPL_YOURHOST
                                003 RPL_CREATED
                                004 RPL_MYINFO
```

Any command other than `PASS`, `NICK`, `USER`, or `QUIT` sent before
registration is complete is rejected with `ERR_NOTREGISTERED`.

### Command Parsing and Dispatch

`parseAndExecute()` in [`Server.cpp`](Server.cpp) splits the raw IRC line:

- If the line starts with `:`, the prefix is extracted and discarded (clients
  do not send meaningful prefix data).
- The remaining string is split on spaces into command and parameters.
- The last parameter starting with `:` is taken verbatim (trailing parameter).
- The command string is matched with a series of comparisons and the
  corresponding function is called, passing the `Client *` and the parameter
  vector.

### Channel Management

**JOIN** ([`commands/join.cpp`](commands/join.cpp)):
- Searches `_channels` by name.
- Creates the channel if not found.
- Checks `+i` (invite-only), `+k` (key), and `+l` (user limit) before
  admitting the client.
- Adds the client to `_members`.
- The very first client to join is automatically added to `_operators`.
- Sends `JOIN` broadcast to all members, then `RPL_TOPIC` or `RPL_NOTOPIC`
  and `RPL_NAMREPLY` + `RPL_ENDOFNAMES` to the joining client.

**PART** ([`commands/part.cpp`](commands/part.cpp)):
- Sends a `PART` broadcast to all channel members including the parting client.
- Removes the client from `_members` and `_operators`.
- Deletes the channel if `_members` is now empty.

**PRIVMSG** ([`commands/privmsg.cpp`](commands/privmsg.cpp)):
- If the target starts with `#` it is a channel message: iterates `_members`
  and sends to every fd except the sender's.
- Otherwise it is a direct message: finds the target client by nickname and
  sends to their fd.
- Returns `ERR_NOSUCHNICK` or `ERR_NOSUCHCHANNEL` if the target is not found.

### Channel Modes

**MODE** ([`commands/mode.cpp`](commands/mode.cpp)) is restricted to channel
operators. The following flags are implemented:

| Flag | Set | Unset | Parameter | Effect |
|------|-----|-------|-----------|--------|
| `i` | `+i` | `-i` | none | Invite-only — only invited users can JOIN |
| `t` | `+t` | `-t` | none | Topic restricted — only operators can use TOPIC |
| `k` | `+k` | `-k` | `<key>` | Channel password — must match on JOIN |
| `l` | `+l` | `-l` | `<limit>` | User limit — JOIN rejected when full |
| `o` | `+o` | `-o` | `<nick>` | Grant or revoke channel operator status |

Each mode change is broadcast to all channel members with the operator's
full `nick!user@host` prefix.

`MODE <#channel>` with no flags sends `RPL_CHANNELMODEIS` showing the current
active modes.

### Operator Privileges

A client becomes a **channel operator** either by being the first to JOIN a
channel or by receiving `+o` from an existing operator. Channel operators are
identified with `@` in the `NAMES` list.

Channel operators can:
- Use `KICK` to remove any member.
- Use `INVITE` to add a user to the invite list (required when `+i` is set).
- Set or change the `TOPIC` when `+t` mode is active.
- Use `MODE` to change any channel flag.

Non-operators attempting these commands receive `ERR_CHANOPRIVSNEEDED`.

**KICK** ([`commands/kick.cpp`](commands/kick.cpp)):
- Verifies the caller is in `_operators`.
- Finds the target by nickname in `_members`.
- Broadcasts `KICK` to all channel members.
- Removes the target from the channel.

**INVITE** ([`commands/invite.cpp`](commands/invite.cpp)):
- Verifies the caller is a channel operator.
- Checks the target nick exists.
- Adds the target to the channel `_invited` list.
- Sends `RPL_INVITING` to the operator and a `INVITE` notice to the target.

**TOPIC** ([`commands/topic.cpp`](commands/topic.cpp)):
- With no trailing parameter: sends `RPL_TOPIC` or `RPL_NOTOPIC`.
- With a trailing parameter: checks `+t` mode — if set, verifies the caller
  is an operator. Sets `_topic` and broadcasts the change to all members.

### IRC Numeric Replies

All numeric reply strings are defined as constants in
[`irc_messages.hpp`](irc_messages.hpp). `sendfillmessage()` in
[`fillmessage.cpp`](fillmessage.cpp) selects the correct format string for
each numeric, fills in the client/channel values, and calls `send()` on the
client's fd:

| Numeric | Constant | Sent by |
|---------|----------|---------|
| `001` | `RPL_WELCOME` | USER (registration complete) |
| `002` | `RPL_YOURHOST` | USER |
| `003` | `RPL_CREATED` | USER |
| `004` | `RPL_MYINFO` | USER |
| `324` | `RPL_CHANNELMODEIS` | MODE (query) |
| `331` | `RPL_NOTOPIC` | JOIN, TOPIC |
| `332` | `RPL_TOPIC` | JOIN, TOPIC |
| `341` | `RPL_INVITING` | INVITE |
| `353` | `RPL_NAMREPLY` | JOIN, NAMES |
| `366` | `RPL_ENDOFNAMES` | JOIN, NAMES |

### Error Handling

| Numeric | Meaning | Sent by |
|---------|---------|---------|
| `401 ERR_NOSUCHNICK` | Target nick does not exist | PRIVMSG, INVITE, KICK |
| `403 ERR_NOSUCHCHANNEL` | Channel does not exist | PART, TOPIC, KICK |
| `404 ERR_CANNOTSENDTOCHAN` | Cannot send to channel | PRIVMSG |
| `431 ERR_NONICKNAMEGIVEN` | No nickname given | NICK |
| `432 ERR_ERRONEUSNICKNAME` | Invalid nickname characters | NICK |
| `433 ERR_NICKNAMEINUSE` | Nickname already taken | NICK |
| `441 ERR_USERNOTINCHANNEL` | Target is not in channel | KICK |
| `442 ERR_NOTONCHANNEL` | Caller is not in channel | PART, TOPIC |
| `461 ERR_NEEDMOREPARAMS` | Missing parameters | all commands |
| `464 ERR_PASSWDMISMATCH` | Wrong server password | PASS |
| `471 ERR_CHANNELISFULL` | Channel is full (`+l`) | JOIN |
| `473 ERR_INVITEONLYCHAN` | Channel is invite-only (`+i`) | JOIN |
| `475 ERR_BADCHANNELKEY` | Wrong channel key (`+k`) | JOIN |
| `482 ERR_CHANOPRIVSNEEDED` | Caller is not a channel operator | KICK, INVITE, TOPIC, MODE |

---

## Build

```bash
make
make clean
make fclean
make re
```

---

## Testing

```bash
# Start the server
./ircserv 6667 testpass

# Basic registration and messaging with nc
nc localhost 6667
PASS testpass
NICK alice
USER alice 0 * :Alice Smith
JOIN #test
PRIVMSG #test :hello from alice

# Second client in a separate terminal
nc localhost 6667
PASS testpass
NICK bob
USER bob 0 * :Bob Smith
JOIN #test
PRIVMSG #test :hello from bob

# Test channel modes (as operator)
MODE #test +i
MODE #test +t
MODE #test +k secretkey
MODE #test +l 5
MODE #test +o bob

# Test operator commands
KICK #test bob :goodbye
INVITE bob #test
TOPIC #test :new topic

# Test with irssi
irssi
/connect localhost 6667 testpass alice
/join #test
/msg #test hello world
```