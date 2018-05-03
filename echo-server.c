#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "echo-server.h"    
#include "menus.h"

//ANSI Codes for better visualization and clearing
#define clear "\e[2J"
#define nounderline "\e[?25l"
#define onunderline "\e[?25h"

#define BUFFER_SIZE   2000
#define QUEUE_LENGTH     5
#define PORT_NUM     10001

typedef int bool;
#define true 1
#define false 0

int main(int argc, char *argv[])    
{

    unsigned long int port_num = arguments(argc, argv);
    int sock, msg_sock;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t client_address_len;

    char buffer[BUFFER_SIZE];
    ssize_t len; //, snd_len;
    
    sock = socket(PF_INET, SOCK_STREAM, 0); // creating IPv4 TCP socket
    if (sock < 0)
        syserr("socket");
    // after socket() call; we should close(sock) on any execution path;
    // since all execution paths exit immediately, sock would be closed when program terminates
  
    //specifying server_address
    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // listening on all interfaces
    server_address.sin_port = htons(port_num); // listening on port PORT_NUM

    // bind the socket to a concrete address
    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        syserr("bind");

    // switch to listening (passive open)
    if (listen(sock, QUEUE_LENGTH) < 0)
        syserr("listen");

    printf("accepting client connections on port %hu\n", ntohs(server_address.sin_port));
    for (;;) {
        client_address_len = sizeof(client_address);
        // get client connection from the socket
       
        msg_sock = accept(sock, (struct sockaddr *) &client_address, &client_address_len);
        if (msg_sock < 0)
            syserr("accept");
       
        printf("Client %d connected to server on port number: %lu\n", msg_sock, port_num);
        
        //Setting up menu (variables and ansi codes for outlook)
        int opt = 0;
        int type = 0;
        int charsoff = write(msg_sock,"\377\375\042\377\373\001",6);
        if(charsoff != 6)
             syserr("writing to client socket");
        charsoff = write(msg_sock, nounderline, 6);
         if(charsoff != 6)
             syserr("writing to client socket");
        
        make_menu(opt, type, msg_sock);
        
        do {
            len = read(msg_sock, buffer, sizeof(buffer));       
            if (len < 0)
                syserr("reading from client socket");
            else {  
                if(buffer[0] == '\033' && buffer[1] == '['){
                    if(buffer[2] == 'B')
                        opt = (opt + 1) % 3;
                    else if(buffer[2] == 'A'){
                         opt = opt - 1;
                        if(opt < 0){
                            opt = 2;
                        }
                    }
                    make_menu(opt, type, msg_sock);
                }
            
                if(buffer[0] == 13){
                    bool swap = false;
                    if(type == 0){
                        if(opt == 1){
                            swap = true;
                            type++;
                         }
                         else if(opt == 2){                         
                             break;
                         }
                    }
                    else if(type == 1){
                        if(opt == 2){
                            type--;
                            swap = true;
                        }
                    }
                    if(swap){
                        opt = 0;
                        make_menu(opt, type, msg_sock);
                    }
                    else
                        make_after_menu(opt, type, msg_sock);
                } 
            }
        } while (len > 0);
        printf("Ending connection with %d\n", msg_sock);
        if (close(msg_sock) < 0)
            syserr("close");
    }
    
  return 0;
}
