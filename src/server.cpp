#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sysexits.h>

#define BACKLOG_LENGTH 10

void read_request(int socket, char* buf, int buflen);

int main(int argc, const char* argv[]) {
  char buf[4096];
  int cfd, fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in si;
  unsigned int addrlen;
  printf("\n\rA dumb server on process %d\n\rJust try connecting to http://127.0.0.1:9586 from your browser ;)\n\r", getpid());

  si.sin_family = PF_INET;
  inet_aton("127.0.0.1", &si.sin_addr);
  si.sin_port = htons(9586);

  if(bind(fd, (struct sockaddr *) &si, sizeof(si)) == -1) return -1;
  if(listen(fd, BACKLOG_LENGTH) == -1) return -1;

  addrlen = sizeof si;
  while((cfd=accept(fd, (struct sockaddr*) &si, (socklen_t *) &addrlen)) != -1) {
    pid_t pid = fork();
    switch(pid) {
      case 0: // child
        printf("listening on socket %d, port %d w/ process %d", cfd, si.sin_port, getpid());
        read_request(cfd, buf, sizeof(buf));
        //write(cfd, "200 OK HTTP/1.0\r\n\r\n"
        //           "Hello galaxy", sizeof("200 OK HTTP/1.0\r\n\r\n") + sizeof("Hello galaxy"));
        if(close(cfd) == -1) {
          printf("closing of stream failed because err %d\n\r", errno);
        };
        printf("exit process %d\n\r", getpid());
        exit(EXIT_SUCCESS);
        break;
      case -1: // fail
        printf("\n\rFailed to spawn a process w/ error %d\n\r", errno);
        break;
      default: // parent
        int status = 0;
        int waitres = waitpid(-1, &status, WNOHANG);
        switch(waitres) {
          case 0:
            break;
          case -1:
            break;
          default:
            printf("witnessed change for %d\n\r", waitres);
            break;
        }
        printf("\n\r%d spawned process %d\n\r", getpid(), pid);
    }
  }
}

void read_request(int socket, char* buf, int buflen) {
  if(socket == -1) return;
  ssize_t bytes = read(socket, buf, buflen);

  if(bytes == -1) {
    printf("\n\rI encountered error %d while reading\n\r", errno);
  } else {
    printf("... received %ld bytes\n\r", bytes);
    //printf(" containing:\n\r=========\n\r%s=========\n\r", buf);
  }
}
