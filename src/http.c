#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 8080;

int main(void) {
  // Open TCP Socket
  //

  int server_fd, new_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len = sizeof(client_addr);

  // Create a socket file descriptor
  char buffer[1024] = {0};

  char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "
                   "12\n\nHello world!";

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Setup server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server started %shttp://127.0.0.1:%d%s\n", "\033[92m", PORT,
         "\033[0m");

  while (1) {
    // Accept incoming

    // Wtf
    // Assign the address length to the size of the client address
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr,
                             &addr_len)) < 0) {
      perror("accept");
      close(server_fd);
      exit(EXIT_FAILURE);
    }

    // read req
    read(new_socket, buffer, 1024);

    send(new_socket, response, strlen(response), 0);

    close(new_socket);
  }

  close(server_fd);

  return 0;
}
