#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
  printf("\nJust reading http://bulk.fefe.de/scalable-networking.pdf\n");

  char buf[4096];
  int len;
  int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in si;
}
