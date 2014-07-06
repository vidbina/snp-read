#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>

int main(int argc, const char* argv[]) {
  printf("\nJust reading http://bulk.fefe.de/scalable-networking.pdf\n");

  char buf[4096];
  ssize_t res, len;
  int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in si;

  si.sin_family = PF_INET;
  inet_aton("127.0.0.1", &si.sin_addr);
  si.sin_port = htons(9586);

  connect(fd, (struct sockaddr *) &si, sizeof si);
  printf("%lu chars in [%s]", sizeof("GET / HTTP/1.0\r\n\r\n\0"), "GET / HTTP/1.0\r\n\r\n\0");
  
  res = write(fd, "GET / HTTP/1.0\r\n\r\n", sizeof("GET / HTTP/1.0\r\n\r\n"));
  switch(res) {
    case 0:
      // read returning info
      len = read(fd, buf, sizeof buf);
      if(len == -1) {
        printf("\n\rerror %d while reading response", errno);
        return(-1);
      }
      break;
    case -1:
      break;
    default:
      break;
  }
  close(fd);
  printf("\ndone\n");
}
