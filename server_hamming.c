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
    struct sockaddr_in serv_addr,client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("[-]Socket error");
        exit(1);
    }
    memset(&serv_addr,'\0',sizeof(serv_addr));
    serv_addr.sin_addr.s_addr=inet_addr(ip);
    serv_addr.sin_port=htons(port);
    serv_addr.sin_family=AF_INET;
    n=bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(n<0){
        perror("[-]Bind error");
        exit(1);
    }
     // bzero(buffer, 1024);
    //   printf("Enter the code word : ");
    //   scanf("%[\n]s",buffer);
    //   printf("Sending the data to server......%s \n",buffer);
    //   sendto(sockfd,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));


    // Receiving form client
     bzero(buffer, 1024);
      addr_size=sizeof(client_addr);
      recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&client_addr, &addr_size);
      printf("Received from the server %s\n",buffer);

      char dummybuf[1024];
      int d1=buffer[3]-'0';
      int d2=buffer[2]-'0';
      int d3=buffer[1]-'0';
      int d4=buffer[0]-'0';
      dummybuf[0]=(d2+d3+d4)%2+'0';
      dummybuf[1]=buffer[2];
      dummybuf[2]=(d1+d3+d4)%2+'0';
      dummybuf[3]=buffer[3];
      dummybuf[4]=(d1+d2+d4)%2+'0';
      dummybuf[5]=buffer[1];
      dummybuf[6]=buffer[0];
      dummybuf[7]='\0';

    //   Sending the data to client
      printf("Sending the code word to the client....%s\n",dummybuf);
      sendto(sockfd,dummybuf,1024,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
      //close(sockfd);
      return 0;
}


