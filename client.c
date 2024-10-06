#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

void error(char* msg){
    perror(msg);
    exit(1);
}


int main(int argc, int argv[]){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostnet *server;//this is a pointer to a structure 
    char buffer[255];

    if(argc < 3){
        error("port no not there");
    }

    portno = atoi(argv[2]);

    //create a socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    server = gethostbyname(argv[1]);

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);//this function coopies a specific number of bytes from one memory location to the to other

    //now lets connect
    if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        error("wrong stuff");
    }

    //now lets see the loop
    while(1){
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));

        n = read(sockfd, buffer, 255);
        printf(buffer);

        int i = strncmp("Bye", buffer, 3)

        if(i == 0){
            break;
        }
    }
}