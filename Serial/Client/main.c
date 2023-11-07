#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define BAUDRATE B921600
#define PORT "/dev/ttyUSB0"
#define BUFFER_CAP 256

char buffer[BUFFER_CAP] = {0};
int buffer_sz = 0;

int
openPort(char *port)
{
  int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("[ERROR] openPort: Could not open port");
    exit(-1);
  }
  fcntl(fd, F_SETFL, 0);
  return fd;
}

void
setPortOptions(struct termios *options, int fd)
{
  if (tcgetattr(fd, options) < 0) {
    perror("[ERROR] setPortOptions: Could not get port attributes");
    exit(-1);
  }
  cfmakeraw(options);
  cfsetispeed(options, BAUDRATE);
  options->c_cflag |= CLOCAL;          // always set
  options->c_cflag |= CREAD;           // always set
  options->c_cflag |= CRTSCTS;         // enable rts/cts
  options->c_cc[VTIME] = 0;            // no timeout
  options->c_cc[VMIN] = 1;             // 1 char satisfies
  if (tcsetattr(fd,TCSANOW,options) < 0) {
      fprintf(stderr, "[ERROR] setPortOptions: could not set attributes %s\n",strerror(errno));
      exit(-1);
  }
}

void
analyzeSerial(char *c)
{
  switch (*c) {
    case '\r': printf("\n"); break;
    case '\n': 
      printf("%s", buffer);
      bzero(buffer, BUFFER_CAP);
      buffer_sz = 0;
      break;
    default:
      buffer[buffer_sz++] = *c;
  }
}

int
main(int argc, char **argv)
{
  char c; // Character to read from serial
  struct termios options; // Serial terminal options
  int fd = openPort(PORT);
  setPortOptions(&options, fd);
  tcflush(fd, TCIFLUSH);
  while(true) {
    if (read(fd, &c, 1) == -1)
      break;
    analyzeSerial(&c);
  }
  return 0;
}