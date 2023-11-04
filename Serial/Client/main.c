#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>


int
openPort(char *port)
{
  int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) perror("[ERROR] openPort: Could not open port");
  fcntl(fd, F_SETFL, 0);
  return fd;
}

int
main(int argc, char **argv)
{
  printf("test\n");
  return 0;
}