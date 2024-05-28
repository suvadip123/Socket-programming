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

// char *crc_stuffing(char *msg,char *crc){
//     char encoded[1024]="";
//     int  m=strlen(msg);
//     int c=strlen(crc);
//     strcat(encoded,msg);
//     int  i;
//     // for(i=1;i<=c-1;i++){
//     //    strcat(encoded,"0");
//     // }
//     for(i=1;i<=c-1;i++){
//       encoded[i]='0';
//     }
//     encoded[i+1]='\0';

//     for(i=0;i<=strlen(encoded)-c;){
//         for(int j=0;j<c;j++){
//             encoded[i+j]=encoded[i+j]==crc[j]? '0':'1';
//         for(;i<strlen(encoded) && encoded[i]!='1';i++);    
//         }
//     }
//     char substri[1024];
//     int e=strlen(encoded);
//     int pos,len,cout;
//     cout=0;
//     pos=e-c+1;
//     len=c-1;
//     while(cout<len){
//         substri[cout]=encoded[pos+cout-1];
//         cout++;
//     }
//     substri[cout]='\0';
//     strcat(msg,substri);
//     return msg;

// }


// modified crc stuffing ........


char *crc_stuffing(char *msg,char *crc){

char rem[1024],temp[1024];
    int msg_len, key_len, i;

    // printf("Enter the dividend :");
    // scanf("%s", msg);

    // printf("Enter the divisor:");
    // scanf("%s", key);

    msg_len = strlen(msg);
    key_len = strlen(crc);

    msg[msg_len] = '\0';
    rem[key_len] = '\0';

    // Append 0 at the end
    strcpy(temp, msg);
    for (i = 0; i < key_len-1; i++)
    {
        temp[msg_len + i] = '0';
    }

    
    // XOR operation
    for (int j = 0; j < msg_len; j++)
    {
        if (temp[j] != '0')
        {
            for (int k = 0; k < key_len; k++)
            {
                rem[k] = temp[j+k] = (temp[j+k] == crc[k]) ? '0' : '1';
            }
        }
        // printf("%s\n",temp);
        // printf("%s\n",rem);
    }
    // printf("%s\n",temp);

    //printf("%s\n",rem);

    // Reduce remainder
    for (int i = 0; i < key_len; i++)
    {
        rem[i] = rem[i+1];
    }
    
   return strcat(msg,rem);



}


int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  char crc[1024];
  char data[1024];
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
    printf("Received From Client: %s \n", buffer);
    bzero(data,1024);
    strcpy(data,"Received");
    send(client_sock,data,strlen(data),0);
    bzero(crc,1024);
    recv(client_sock, crc, sizeof(crc), 0);
    printf("Received From Client: %s \n", crc);
    char *crc_data=(char*)malloc(strlen(buffer)*2+1);
    char *crc_data=crc_stuffing(buffer,crc);
    printf("Sending Crc-Stuffing code to Client \n");
    send(client_sock,crc_data , strlen(crc_data), 0);
    free(crc_data);
    close(server_sock);

    close(client_sock);
    printf("[+]Client disconnected.\n\n");

 //}

  return 0;
}