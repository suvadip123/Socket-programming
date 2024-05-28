//include the header  files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char **argv){
    if(argc!=2){
        printf("USAGE %s <port>",argv[0]);
        exit(0);
    }
    char *ip="127.0.0.1";
    int port=atoi(argv[1]);
    int sockfd;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("[-]Socket error");
        exit(1);
    }

    memset(&addr,'\0',sizeof(addr));
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(port);
    addr.sin_family=AF_INET;
//    Sending the data to  the server
      bzero(buffer, 1024);
      printf("Enter the code word : ");
      scanf("%[^\n]s",buffer);
      printf("Sending the data to server......%s \n",buffer);
      sendto(sockfd,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));
// Receiving the data from client
      addr_size=sizeof(addr);
      recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&addr, &addr_size);
      printf("Received from the server %s\n",buffer);
      //close(sockfd);
      return 0;
}


