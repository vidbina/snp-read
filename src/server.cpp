#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>

#define BACKLOG_LENGTH 10

void read_request(int socket, char* buf, int buflen);

int main(int argc, const char* argv[]) {
  char buf[4096];
  int cfd, fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in si;
  unsigned int addrlen;
  printf("\nA dumb server on process %d\n\rJust try connecting to http://127.0.0.1:9586 from your browser ;)\n\r", getpid());

  si.sin_family = PF_INET;
  inet_aton("127.0.0.1", &si.sin_addr);
  si.sin_port = htons(9586);

  if(bind(fd, (struct sockaddr *) &si, sizeof(si)) == -1) return -1;
  if(listen(fd, BACKLOG_LENGTH) == -1) return -1;

  addrlen = sizeof si;
  while((cfd=accept(fd, (struct sockaddr*) &si, (socklen_t *) &addrlen)) != -1) {
    printf("\n\rlistening on port %d w/ process %d\n\r", si.sin_port, getpid());
    read_request(cfd, buf, sizeof(buf));
    write(cfd, "200 OK HTTP/1.0\r\n\r\n"
               "Hello galaxy", sizeof("200 OK HTTP/1.0\r\n\r\n") + sizeof("Hello galaxy"));
    close(cfd);
  }
}

void read_request(int socket, char* buf, int buflen) {
  if(socket == -1) return;
  int bytes = read(socket, buf, buflen);
  printf("I just received %d bytes with error %d containing:\n\r=========\n\r%s\n\r=========\n\r\n\r", bytes, errno, buf);
}
