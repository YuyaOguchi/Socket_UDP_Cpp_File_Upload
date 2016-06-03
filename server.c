//
// COEN 146L lab2
// Yuya Oguchi
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    ////////// same for UDP TCP //////////////
    //info about IP itself
    struct sockaddr_in si_server;
    bzero((char*)&si_server, sizeof(si_server));
    si_server.sin_family = AF_INET;
    //copy server content to si_server to avoid changing pointer
    si_server.sin_addr.s_addr = INADDR_ANY;
    si_server.sin_port = htons(5555);
    //////////////////////////////////////////
    //////////// UDP Specified ///////////////
    int sockfd = socket(PF_INET,SOCK_DGRAM,0);
    bind(sockfd,(struct sockaddr *)&si_server, sizeof(si_server));

    //init buffer and sizes server will get from client
    char buffer[256];
    int name;
    int content;

    //length of name of socket addr
    socklen_t l = sizeof(si_server);

    //receive new file name
	name = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&si_server, &l);
    printf("file name %s received\n", buffer);

    //open new file
    FILE *file;
    file = fopen(buffer,"w");

    //receive new file contents
    content = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&si_server, &l);
    //write to new file
    fputs(buffer,file);
    printf("file content %s received\n",buffer);

    //close file
    fclose(file);

return 1;
}
