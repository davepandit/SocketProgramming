#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet.h>


void error(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        error("Port number not provided");
    }
    //decalring some sort of variables 
    int sockfd, newsockfd, portno, n;
    char buffer[255];

    //instance of the structure
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    //sockaddr_in is a structure and basically have some variables as the address family, ip address, and the port number so basically a structure is made to make the lives easy
    //and we have sock_len as a datatype that is used to define the size of the address structure of the client basically it is used to define the size of some datatypes such as the sockaddr_in types ke objects and all

    //now lets make the socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("error in creating the socket in the server side");
    }
    //some sort of clearing
    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    //three imp initialisation 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //binding the socket with some ip address and a port no
    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        error("some error occured in binding the socket");
    }

    //listen for some connections
    listen(sockfd, 5);
    //5 here means the max number of connections that can be made to the server at a time

    //then the client will reqest some sort of connection and then we need to accept it 
    clilen = sizeof(cli_addr);

    //acceoting the connection 
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

    //some checks
    if(newsockfd < 0){
        error("connection request not accepted");
    }

    //loop to keep on listening to the req
    while(1){
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);
        //for this to work there should be some write function in the client side
        //the message will be in the buffer
        if(n < 0){
            error("there is some error in reading");
        }
        printf("Buffer is:%s", buffer);

        //again clear the buffer
        bzero(buffer, 255);
        //in the upper part the server is listening to the write operations from the client and now the server will be writing something that we need to send to the client
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));

        if(n < 0){
            error("error in writing");
        }

        //so like when the user types bye then the connection in between the server and the client should stop
        int i = strncmp("Bye", buffer, 3);
        if(i == 0){
            break;
        }
    }
    //then close the connection 
        close(newsockfd);
        close(sockfd);
        return 0;
}
