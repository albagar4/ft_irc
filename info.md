## Puede que falten algunas, creo que estas son las más importantes / las que vamos a usar

### socket | int socket(int domain, int type, int protocol);

- domain: AF_INET o AF_INET6, el tipo de IP, es decir IPv4 o IPv6
- type: SOCK_STREAM o SOCK_DGRAM, el tipo de conexión, es decir TCP o UDP
- protocol: normalmente 0
- return: file descriptor del nuevo socket, o -1 en caso de error

Crea un socket (file descriptor) para una dirección de red IPv4 con conexión TCP (iniciar servidor)

```cpp
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1)
  throw SOCKET_ERR;
```

### close | int close(int sockfd);

- sockfd: el file descriptor del socket
- return: 0 o -1

Cierra un socket (desconectar cliente)

```cpp
if (close(sockfd) == -1)
  throw CLOSE_ERR;
```

### setsockopt | int setsockopt(int sockfd, int level, int option_name, const void \*option_value, socklen_t option_len);

- sockfd: v. `close`
- level: nivel del protocolo, normalmente SOL_SOCKET
- option_name: opciones del socket como SO_REUSEADDR, SO_RCVBUF, SO_SNDBUF, etc.
- option_value: puntero al valor de las opciones a setear
- option_len: tamaño de option_value
- return: 0 o -1

Modifica las opciones de un socket

```cpp
if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
  throw SOCKET_OPTION_ERR;
```

### getsockname | int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

- sockfd: v. `close`
- addr: puntero a una estructura `sockaddr` con la dirección del socket
- addrlen: puntero al tamaño de `addr`
- return : 0 o -1

Consigue la dirección de un socket

```cpp
struct sockaddr_in addr;
socklen_t addrlen = sizeof(addr);

if (getsockname(sockfd, (struct sockaddr *)&addr, &addrlen) == 0) {
  std::cout << "Local IP address: " << addr.sin_addr;
  ...
} else {
  throw GETSOCKNAME_ERR;
}
```

### bind | int bind(int sockfd, const struct sockaddr \*addr, socklen_t addrlen);

- sockfd: v. `close`
- addr: puntero a la estructura `sockaddr` con la IP y el puerto a conectar
- addrlen: tamaño de `addr`
- return: 0 o -1

Asocia un socket con una dirección IP y puerto. Se usaría al inicio para conectar el socket con nuestra IP/puerto e iniciar el servidor

```cpp
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to any local IP
server_addr.sin_port = htons(8080);        // Bind to port 8080

if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind failed");
}
```

### connect | int connect(int sockfd, const struct sockaddr \*addr, socklen_t addrlen);

- sockfd: v. `close`
- addr: v. `bind`
- addrlen: v. `bind`
- return: 0 o -1
  Inicia la conexión entre un socket y el servidor

```cpp
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8080);
inet_pton(AF_INET, "192.168.1.1", &server_addr.sin_addr);  // Set the server IP address

if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("connect failed");
}
```

### listen | int listen(int sockfd, int backlog);

- sockfd: v. `close`
- backlog: número de conexiones pendientes máximas
- return: 0 o -1

Activa un socket para que escuche conexiones externas

```cpp
if (listen(sockfd, 10) == -1) {  // Allow a maximum of 10 pending connections
    perror("listen failed");
}
```

### accept | int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

- sockfd: v. `close`
- addr: v. `bind`
- addrlen: v. `bind`
- return: el socket del cliente, o -1

Acepta la petición de conexión de un cliente en la cola de conexiones y crea un socket para esa conexión

```cpp
struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);

int new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
if (new_sockfd == -1) {
    perror("accept failed");
} else {
    std::cout << "Connection accepted from client.\n";
}
```

### htons | uint16_t htons(uint16_t hostshort);

- hostshort: el puerto a convertir
- return: el puerto transformado en puerto de red

Transforma un entero de 16 bits (puerto) del orden que sea a un orden de bits para su uso como puerto red. Es decir, cuando se vaya a asignar un puerto, se hace tras convertirlo con `htons`. El resto de funciones de este estilo hacen lo mismo pero con un entero de 32 bits (`htonl`), o al revés con 16 bits (`ntohs`) y con 32 bits (`ntohl`)

```cpp
uint16_t port = 8080;
uint16_t network_port = htons(port);  // Convert to network byte order
```

### inet_addr | in_addr_t inet_addr(const char \*cp);

- cp: string con la IP
- return: IP transformada en binario

Transforma una IP en notación habitual (192.168.1.1) en un entero binario de 32 bits. `inet_ntoa` hace lo mismo pero al revés

```cpp
const char *ip_str = "192.168.0.1";
in_addr_t ip_binary = inet_addr(ip_str);

if (ip_binary == INADDR_NONE) {
    std::cerr << "Invalid IP address\n";
} else {
    std::cout << "IP address in binary: " << ip_binary << "\n";
}
```

### send | ssize_t send(int sockfd, const void \*buffer, size_t length, int flags);

- sockfd: v. `close`
- buffer: puntero a un buffer donde esté la información a enviar
- length: tamaño de buffer
- flags: opciones, usualmente 0
- return: los bytes enviados, o -1

Envía un string a un socket

```cpp
const char *message = "Hello, client!";
ssize_t bytes_sent = send(sockfd, message, strlen(message), 0);

if (bytes_sent == -1) {
    perror("send failed");
} else {
    std::cout << "Sent " << bytes_sent << " bytes.\n";
}
```

### recv | ssize_t recv(int sockfd, void \*buffer, size_t length, int flags);

- sockfd: v. `close`
- buffer: puntero a un buffer donde almacenar el string que se recive
- length: tamaño máximo del buffer
- flags: opciones, usualmente 0
- return: los bytes enviados, **0 si la conexión ha sido cerrada por el cliente**, o -1

Recive información de un socket. Si no se ha configurado como "non-blocking", bloqueará el proceso

```cpp
char buffer[1024];
ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

if (bytes_received == -1) {
    perror("recv failed");
} else if (bytes_received == 0) {
    std::cout << "Connection closed by the peer.\n";
} else {
    buffer[bytes_received] = '\0';  // Null-terminate the buffer
    std::cout << "Received message: " << buffer << "\n";
}
```

### fcntl | int fcntl(int fd, int cmd, ... /_ arg _/ );

- fd: v. `close`
- cmd: comando para especificar la acción, en nuestro caso `F_SETFL`
- arg: argumentos opcionales, en nuestro caso `O_NONBLOCK`
- return: el valor de la operación, o -1

Modifica un fd. Lo usaremos para hacer que los sockets sean "non-blocking" y así poder leer de varios sockets y correr el programa sin necesidad de hilos o hijos

```cpp
if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
    perror("fcntl F_SETFL failed");
    close(fd);
    return 1;
```

### poll / select / kqueue / epoll

Estas funciones sirven para monitorizar un socket, ver si está mandando información, si sigue activo, etc. Antes de cada llamada a `recv` o `send` **es obligatorio usar esta función** Hay que elegir una, `poll` y `select` parecen las más sencillas

### poll | int poll(struct pollfd \*fds, nfds_t nfds, int timeout);

- fds: puntero a un array de estructuras `pollfd`, donde cada una especifica un fd
- nfds: número de fds en el array
- timeout: tiempo máximo para llevar a cabo la comprobación, en nuestro caso 0 (non-blocking)
- return: número de fds con eventos, o -1

```cpp
int main() {
    struct pollfd fds[2];
    fds[0].fd = STDIN_FILENO;    // Monitor standard input (keyboard input)
    fds[0].events = POLLIN;      // Monitor for readability
    fds[1].fd = some_socket_fd;  // Assume some_socket_fd is a valid socket
    fds[1].events = POLLIN;      // Monitor for readability

    int ret = poll(fds, 2, 5000);  // Wait up to 5 seconds

    if (ret == -1) {
        perror("poll failed");
    } else if (ret == 0) {
        std::cout << "Timeout occurred! No data within 5 seconds.\n";
    } else {
        if (fds[0].revents & POLLIN) {
            std::cout << "Data available on stdin.\n";
        }
        if (fds[1].revents & POLLIN) {
            std::cout << "Data available on socket.\n";
        }
    }
    return 0;
}
```

### select | int select(int nfds, fd_set *readfds, fd_set \*writefds, fd_set \*exceptfds, struct timeval *timeout);

- nfds: el mayor fd disponible + 1 (es decir, si hay que monitorear 100 fds, sería 101)
- readfds: puntero a un `fd_set` que representa los fds a observar por lectura
- writefds: puntero a un `fd_set` que representa los fds a observar por escritura
- exceptfds: puntero a un `fd_set` que representa los fds a observar por condiciones excepcionales
- timeout: puntero a una estructura `timeval`, en nuestro caso la estructura debe tener 0 (non-blocking)
- return: número de fds con eventos, o -1

```cpp
int main() {
    fd_set readfds;
    FD_ZERO(&readfds);           // Initialize the set
    FD_SET(STDIN_FILENO, &readfds); // Monitor standard input

    struct timeval timeout;
    timeout.tv_sec = 5;          // 5 seconds timeout
    timeout.tv_usec = 0;

    int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select failed");
    } else if (ret == 0) {
        std::cout << "Timeout occurred! No data within 5 seconds.\n";
    } else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            std::cout << "Data available on stdin.\n";
        }
    }
    return 0;
}
```

`poll` tiene la info en una estructura que se setean con macros, `select` la tiene directamente en variables que se setean con funciones, pero funcionan igual
