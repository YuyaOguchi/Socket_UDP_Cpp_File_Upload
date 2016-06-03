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

    //arg input filename hostname
int main(int argc, char *argv[]){
    ////////// same for UDP TCP //////////////
    struct hostent *server;
    //info about IP itself
    struct sockaddr_in si_server;
    //local host name
    server = gethostbyname(argv[2]);
    bzero((char*)&si_server, sizeof(si_server));
    si_server.sin_family = AF_INET;
    //copy server content to si_server to avoid changing pointer
    bcopy((char*)server->h_addr,(char*)&si_server.sin_addr,server->h_length);
    //address of the local host port
    si_server.sin_port = htons(5555);
    //////////////////////////////////////////
    //////////// UDP Specified ///////////////
    int sockfd = socket(PF_INET,SOCK_DGRAM,0);

    socklen_t socklength = sizeof(si_server);

    // open file -> retrieve & store contents
    FILE *file;
    file = fopen(argv[1],"r");
    //get new file name & store it
    //send file name to server(argv[3]) (hardcode it as sent.txt)
    sendto(sockfd,argv[3],10,0,(struct sockaddr *)&si_server,socklength);
    printf("file name %s sent\n",argv[3]);

    //init and fill buffer with file content
    char buffer [256];
    fgets(buffer, 256, (FILE*)file);
    printf("file content is %s \n",buffer);

    //send contents to server
    sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&si_server,socklength);
    printf("content in buffer sent\n");
    fclose(file);

return 1;
}
