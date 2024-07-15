#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8085
#define BUFFER_SIZE 1024

volatile int keep_running = 1;
int server_fd;

void handle_sigint(int sig) {
  keep_running = 0;
  // We can't use printf here, so we'll write directly to stderr
  const char msg[] = "\nClosing server...\n";
  write(2, msg, sizeof(msg) - 1);
  close(server_fd);
}

// Custom strlen function
size_t my_strlen(const char *str) {
  size_t len = 0;
  while (*str++)
    len++;
  return len;
}

// Custom memset function
void *my_memset(void *s, int c, size_t n) {
  unsigned char *p = s;
  while (n--)
    *p++ = (unsigned char)c;
  return s;
}

int main() {
  int new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE];
  my_memset(buffer, 0, BUFFER_SIZE);

  // Set up SIGINT handler
  struct sigaction act;
  act.sa_handler = handle_sigint;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction(SIGINT, &act, 0);

  // Creating socket file descriptor
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Binding the socket to the network address and port
  bind(server_fd, (struct sockaddr *)&address, sizeof(address));

  // Listening for incoming connections
  listen(server_fd, 3);

  // We can't use printf, so we'll write directly to stdout
  const char msg[] = "Server listening on port 8085. Press Ctrl-C to stop.\n";
  write(1, msg, sizeof(msg) - 1);

  while (keep_running) {
    // Accepting a new connection
    new_socket =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    if (new_socket < 0) {
      // accept() failed or was interrupted
      continue;
    }

    // Reading incoming request
    read(new_socket, buffer, BUFFER_SIZE);

    // Sending HTTP response
    const char *response =
        "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello, World!";
    write(new_socket, response, my_strlen(response));

    // Closing the connected socket
    close(new_socket);
  }

  const char end_msg[] = "Server closed.\n";
  write(1, end_msg, sizeof(end_msg) - 1);
  return 0;
}
