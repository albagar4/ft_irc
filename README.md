<div align="center">
    <!-- <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/ft-irc-light.png?raw=true#gh-light-mode-only" alt="Banner (claro)" /> -->
    <!-- <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/ft-irc-dark.png?raw=true#gh-dark-mode-only" alt="Banner (oscuro)" /> -->
    <br>
  This project is about recreating your own IRC server. You will use an actual IRC client to connect to your server and test it.
  Internet is ruled by solid standars protocols that allow connected computers to interact with each other.
  It's always a good thing to know.
    <br>
	<table>
	<tr><th>Albagar4 (Authentification, server initialization)</th>
		<td><a href='https://profile.intra.42.fr/users/albagar4' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/></td>
	</tr>
	<tr><th>Escastel (Messaging, bonus)</th>
		<td><a href='https://profile.intra.42.fr/users/escastel' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/></td>
	</tr>
	<tr><th>Alvega-g (Channels, operator)</th>
		<td><a href='https://profile.intra.42.fr/users/alvega-g' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/><br></td>
	</tr>
	</table>    
    <img src="https://img.shields.io/badge/score- 125%20%2F%20100-success?color=%2312bab9&style=flat" />
    </a>
<div>
	<img src="https://i.ibb.co/tQjS65G/Screenshot-from-2024-12-03-13-55-28.png"/>
</div>
</div>

---

# Mandatory part

<table>
  <tr>
    <th>Program name</th>
    <td><em>ircserv</em></td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td><code>Makefile, *.{h, hpp}, *.cpp, *.tpp, *.ipp</code>, an optional configuration file</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td><code>NAME, all, clean, fclean, re, bonus</code></td>
  </tr>
  <tr>
	<th>Arguments</th>
	<td>port: The listnening port<br>password: The connection password</td>
  </tr>
  <tr>
    <th>External functions</th>
    <td>
      Everything in C++ 98<br>
      <code> socket, close, setsockopt, getsockname, getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo, bind, connect, listen, accept, htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa, send, recv, signal, sigaction, lseek, fstat, fcntl, poll (or equivalent) </code>
	</td>
  </tr>
  <tr>
	<th>Libft authorized</th>
	<td>n/a</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>An IRC server in C++ 98</td>
  </tr>
</table>

You have to develop an IRC server in C++ 98.

You **mustn’t** develop a client.
You **mustn’t** handle server-to-server communication.
Your executable will be run as follows:

```bash
./ircserv <port> <password>
```

- port: The port number on which your IRC server will be listening to for incoming
  IRC connections.
- password: The connection password. It will be needed by any IRC client that tries
  to connect to your server.

#### Even if poll() is mentionned in the subject and the evaluation scale, you can use any equivalent such as select(), kqueue(), or epoll().

# Requirements

- The server must be capable of handling multiple clients at the same time and never
  hang.
- Forking is not allowed. All I/O operations must be **non-blocking**.
- Only 1 poll() (or equivalent) can be used for handling all these operations (read,
  write, but also listen, and so forth).

#### Because you have to use non-blocking file descriptors, it is possible to use read/recv or write/send functions with no poll() (or equivalent), and your server wouldn’t be blocking. But it would consume more system resources. Thus, if you try to read/recv or write/send in any file descriptor without using poll() (or equivalent), your grade will be 0.

- Several IRC clients exist. You have to choose one of them as a **reference**. Your
  reference client will be used during the evaluation process.
- Your reference client must be able to connect to your server without encountering
  any error.
- Communication between client and server has to be done via TCP/IP (v4 or v6).
- Using your reference client with your server must be similar to using it with any
  official IRC server. However, you only have to implement the following features:
  - You must be able to authenticate, set a nickname, a username, join a channel,
    send and receive private messages using your reference client.
  - All the messages sent from one client to a channel have to be forwarded to
    every other client that joined the channel.
  - You must have **operators** and regular users.
  - Then, you have to implement the commands that are specific to **channel
    operators**:
    - KICK - Eject a client from the channel
    - INVITE - Invite a client to a channel
    - TOPIC - Change or view the channel topic
    - MODE - Change the channel’s mode:
      - i: Set/remove Invite-only channel
      - t: Set/remove the restrictions of the TOPIC command to channel
        operators
      - k: Set/remove the channel key (password)
      - o: Give/take channel operator privilege
      - l: Set/remove the user limit to channel
- Of course, you are expected to write a clean code.

# Test example

Verify absolutely every possible error and issue (receiving partial data, low bandwidth,
and so forth).
To ensure that your server correctly processes everything that you send to it, the
following simple test using nc can be done:

```bash
\$> nc -C 127.0.0.1 6667
com^Dman^Dd
\$>
```

Use ctrl+D to send the command in several parts: ’com’, then ’man’, then ’d\n’.
In order to process a command, you have to first aggregate the received packets in
order to rebuild it.

# Bonus part

Here are the extra features you can add to your IRC server so it looks even more like and
actual IRC server:

- Handle file transfer.
- A bot.

# How to run

Clone this repository and execute it by running the following commands:

```bash
git clone https://github.com/albagar4/ft_irc.git
cd ft_irc
make
./ircserv 6667 supersecurepassword
```
