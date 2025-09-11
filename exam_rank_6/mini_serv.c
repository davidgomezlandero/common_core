#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Globals
typedef struct s_client {
  int id;
  char msg[370000]; // buffers might need to be changed
} t_client;
t_client clients[2048];
fd_set read_set, write_set, current;
int maxfd = 0, gid = 0;
char send_buffer[400000], recv_buffer[400000];  // buffers might need to be changed

// Error message
void err(char *msg) {
  if (msg)
    write(2, msg, strlen(msg));
  else
    write(2, "Fatal error", 11);
  write(2, "\n", 1);
  exit(1);
}

// Send message to all clients
void send_to_all(int except) {
  printf("%s", send_buffer); // not sure if this printf is needed
  for (int fd = 0; fd <= maxfd; fd++) {
    if (FD_ISSET(fd, &write_set) && fd != except) {
      if (send(fd, send_buffer, strlen(send_buffer), 0) == -1)
        err(NULL);
    }
  }
}

int main(int ac, char **av) {
  if (ac != 2)
    err("Wrong number of arguments");

  struct sockaddr_in serveraddr; // Initialization of server struct
  socklen_t len = sizeof(struct sockaddr_in);
  int serverfd = socket(AF_INET, SOCK_STREAM, 0); // Create the server socket
  if (serverfd == -1)
    err(NULL);

  maxfd = serverfd; // Set that socket as the current maximum fd

  FD_ZERO(&current);          // Clean the current set
  FD_SET(serverfd, &current); // Add the server to the current set

  bzero(clients, sizeof(clients));        // Clean the clients struct
  bzero(&serveraddr, sizeof(serveraddr)); // Clean the server struct

  serveraddr.sin_family = AF_INET; // Configure the server for IPv4
  serveraddr.sin_addr.s_addr = htonl(2130706433);  // Accept connections from 127.0.0.1
  serveraddr.sin_port = htons(atoi(av[1])); // Configure the port

  if (bind(serverfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1 ||
      listen(serverfd, 100) == -1) // Bind and listen to the server socket
    err(NULL);

  while (1) {
    read_set = write_set = current; // Reset sets to the current
    if (select(maxfd + 1, &read_set, &write_set, 0, 0) == -1) // Wait for changes
      continue;
    for (int fd = 0; fd <= maxfd; fd++) { // Run through the avaliable sockets
      if (FD_ISSET(fd, &read_set)) { // If a socket is ready to be read from
        if (fd == serverfd) {        // If that socket is the server
          int clientfd = accept(serverfd, (struct sockaddr *)&serveraddr, &len); // Accept a new connection
          if (clientfd == -1)
            continue;
          if (clientfd > maxfd) // Update the new max fd
            maxfd = clientfd;
          clients[clientfd].id = gid++; // Assing an ID and increment the global ID counter
          FD_SET(clientfd, &current); // Add the fd to the current set
          sprintf(send_buffer, "server: client %d just arrived\n", clients[clientfd].id);
          send_to_all(clientfd);
          break;
        } else { // If that socket is not the server
          int ret = recv(fd, recv_buffer, sizeof(recv_buffer), 0); // Read from it
          if (ret <= 0) { // If no bytes sent, disconnect client
            sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
            send_to_all(fd);
            FD_CLR(fd, &current); // Remove the fd from the current set
            close(fd);
            bzero(clients[fd].msg, strlen(clients[fd].msg));
            break;
          } else { // If there are bytes, read the message
            for (int i = 0, j = strlen(clients[fd].msg); i < ret; i++, j++) {
              clients[fd].msg[j] = recv_buffer[i]; // Copy the message from the buffer to the client
              if (clients[fd].msg[j] == '\n') { // If newline is found, cut and send the message
                clients[fd].msg[j] = '\0';
                sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                send_to_all(fd);
                bzero(clients[fd].msg, strlen(clients[fd].msg));
                j = -1;
              }
            }
          }
        }
      }
    }
  }
  return (0);
}