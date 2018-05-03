#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "err.h"

void syserr(const char *fmt, ...)
{
  va_list fmt_args;
  int errno1 = errno;

  fprintf(stderr, "ERROR: ");
  va_start(fmt_args, fmt);
  vfprintf(stderr, fmt, fmt_args);
  va_end(fmt_args);
  fprintf(stderr, " (%d; %s)\n", errno1, strerror(errno1));
  exit(EXIT_FAILURE);
}

void fatal(const char *fmt, ...)
{
  va_list fmt_args;

  fprintf(stderr, "ERROR: ");
  va_start(fmt_args, fmt);
  vfprintf(stderr, fmt, fmt_args);
  va_end(fmt_args);
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}

unsigned long int arguments(int argc, char *argv[]){
  if(argc != 2){
      fprintf(stderr, "ERROR: WRONG NUMBER OF ARGUMENTS!\n");
      exit(1);
  }
  
  unsigned long int port_num = 0;
  for(unsigned int i = 0; i < strlen(argv[1]); i++){
      //printf("%c\n", argv[1][i]);
      if(argv[1][i] < '0' || argv[1][i] > '9'){
          fprintf(stderr, "ERROR: ARGUMENTS IS NOT A DECIMAL NUMBER!\n");
          exit(1);
      }
      port_num = port_num * 10 + argv[1][i] - '0';
      if(port_num > 65535){
          fprintf(stderr, "ERROR: PORT NUMBER IS TOO LARGE!\n");
          exit(1);
      }
  }
  return port_num;
}
