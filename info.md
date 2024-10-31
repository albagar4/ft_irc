## Puede que falten algunas, creo que estas son las más importantes / las que vamos a usar

# socket | int socket(int domain, int type, int protocol);

- domain: AF_INET o AF_INET6, el tipo de IP, es decir IPv4 o IPv6
- type: SOCK_STREAM o SOCK_DGRAM, el tipo de conexión, es decir TCP o UDP
- protocol: normalmente 0
- return: file descriptor del nuevo socket, o -1 en caso de error

Crea un socket (file descriptor) para una dirección de red IPv4 con conexión TCP (iniciar servidor)

```
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1)
  throw SOCKET_ERR;
```

# close | int close(int sockfd);

- sockfd: el file descriptor del socket
- return: 0 o -1

Cierra un socket (desconectar cliente)

```
if (close(sockfd) == -1)
  throw CLOSE_ERR;
```

# setsockopt | int setsockopt(int sockfd, int level, int option_name, const void \*option_value, socklen_t option_len);

- sockfd: v. `close`
- level: nivel del protocolo, normalmente SOL_SOCKET
- option_name: opciones del socket como SO_REUSEADDR, SO_RCVBUF, SO_SNDBUF, etc.
- option_value: puntero al valor de las opciones a setear
- option_len: tamaño de option_value
- return: 0 o -1

Modifica las opciones de un socket

```
if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
  throw SOCKET_OPTION_ERR;
```

# getsockname | int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

- sockfd: v. `close`
- addr: puntero a una estructura `sockaddr` con la dirección del socket
- addrlen: puntero al tamaño de `addr`
- return : 0 o -1

Consigue la dirección de un socket

```
struct sockaddr_in addr;
socklen_t addrlen = sizeof(addr);

if (getsockname(sockfd, (struct sockaddr *)&addr, &addrlen) == 0) {
  std::cout << "Local IP address: " << addr.sin_addr;
  ...
} else {
  throw GETSOCKNAME_ERR;
}
```

# bind | int bind(int sockfd, const struct sockaddr \*addr, socklen_t addrlen);

- sockfd: v. `close`
- addr: puntero a la estructura `sockaddr` con la IP y el puerto a conectar
- addrlen: tamaño de `addr`
- return: 0 o -1

Asocia un socket con una dirección IP y puerto. Se usaría al inicio para conectar el socket con nuestra IP/puerto e iniciar el servidor

```
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to any local IP
server_addr.sin_port = htons(8080);        // Bind to port 8080

if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind failed");
}
```

# connect | int connect(int sockfd, const struct sockaddr \*addr, socklen_t addrlen);

- sockfd: v. `close`
- addr: v. `bind`
- addrlen: v. `bind`
- return: 0 o -1
  Inicia la conexión entre un socket y el servidor

```
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8080);
inet_pton(AF_INET, "192.168.1.1", &server_addr.sin_addr);  // Set the server IP address

if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("connect failed");
}
```

# listen | int listen(int sockfd, int backlog);

- sockfd: v. `close`
- backlog: número de conexiones pendientes máximas
- return: 0 o -1

Activa un socket para que escuche conexiones externas

```
if (listen(sockfd, 10) == -1) {  // Allow a maximum of 10 pending connections
    perror("listen failed");
}
```

# WIP

# accept | int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

# htons | uint16_t htons(uint16_t hostshort);
