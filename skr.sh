#!/bin/bash
gcc -Wall -Wextra -O2 echo-server.c err.c menus.c
./a.out 10201
fuser -k 10201/tcp
fuser -k 98/tcp
fuser -k 80/tcp
fuser -k 10201/tcp
