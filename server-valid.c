#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// char * bit_stuffing(char *input){
//     char *stuffed_output=(char*)malloc(strlen(input)*2+1);
//     int  stuffed_index=0;
//     int  count= 0;
//     int i;
//     for(i=0;input[i]!='\0';i++){
//         stuffed_output[stuffed_index++]=input[i];
//         if(input[i]=='1'){
//             count++;
//             if(count==5){
//                   stuffed_output[stuffed_index++]='0';
//                   count=0;

//             }
//         }
//         else{
//             count=0;
//         }

//     }
//     stuffed_output[stuffed_index]='\0';
//     return  stuffed_output;

// }

int is_valid_ipv4(const char*ip){
    struct sockaddr_in sa;
    return inet_pton(AF_INET,ip,&(sa.sin_addr))!=0;
}

int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  //char str[1024];
  int n;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  printf("Listening...\n");
    // addr_size = sizeof(client_addr);
    // client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    // printf("[+]Client connected.\n");
   

  //while(1){
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");
    // addr_size = sizeof(client_addr);
    // client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    // printf("[+]Client connected.\n");


    bzero(buffer, 1024);
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Received From Client: %s\n", buffer);

    //bzero(buffer, 1024);
    //bzero(str, 1024);
    // printf("Enter the data word to client");
    // scanf("%[^\n]s",buffer);
    //strcpy(buffer, str);
    // printf("Server: %s\n", buffer);
    // char *stuffed_data=bit_stuffing(buffer);
    // printf("Sending Bit-Stuffing code to Client");
    // send(client_sock,stuffed_data , strlen(stuffed_data), 0);
    // free(stuffed_data);
    //char data[1024];
    
    bzero(buffer,1024);
    if(is_valid_ipv4(buffer)){
        // bzero(buffer,1024);
        strcpy(buffer,"YES");
        send(client_sock,buffer,strlen(buffer),0);
    }
    else{
        // bzero(buffer,1024);
        strcpy(buffer,"NO");
        send(client_sock,buffer,strlen(buffer),0);

    }
    close(server_sock);

    close(client_sock);
    printf("[+]Client disconnected.\n\n");

 //}

  return 0;
}