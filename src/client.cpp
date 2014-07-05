#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
  printf("\nJust reading http://bulk.fefe.de/scalable-networking.pdf\n");

  char buf[4096];
  int len;
  int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in si;

  si.sin_family = PF_INET;
  inet_aton("127.0.0.1", &si.sin_addr);
  si.sin_port = htons(9586);

  connect(fd, (struct sockaddr *) &si, sizeof si);
  printf("length of [%s] is %lu", "GET / HTTP/1.0\r\n\r\n", sizeof "GET / HTTP/1.0\r\n\r\n");
  write(fd, "GET / HTTP/1.0\r\n\r\n", sizeof "GET / HTTP/1.0\r\n\r\n");
  len = read(fd, buf, sizeof buf);
  close(fd);
  printf("\ndone\n");
}
