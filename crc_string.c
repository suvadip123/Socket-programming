#include <stdio.h>
#include<string.h>



int main(){
    char msg[1024]="100000001";
    char crc[1024]="1101";
    char encoded[1024]="";
    int  m=strlen(msg);
    int c=strlen(crc);
    strcat(encoded,msg);
    int  i;
    // for(i=1;i<=c-1;i++){
    //    strcat(encoded,"0");
    // }
    for(i=1;i<=c-1;i++){
      encoded[i]='0';
    }
    encoded[i+1]='\0';

    for(i=0;i<=strlen(encoded)-c;){
        for(int j=0;j<c;j++){
            encoded[i+j]=encoded[i+j]==crc[j]? '0':'1';
        for(;i<strlen(encoded)&&encoded[i]!='1';i++);    
        }
    }
    char substri[1024];
    int e=strlen(encoded);
    int pos,len,cout;
    cout=0;
    pos=e-c+1;
    len=c-1;
    while(cout<len){
        substri[cout]=encoded[pos+cout-1];
        cout++;
    }
    substri[cout]='\0';
    
    printf("Final string is : %s ",strcat(msg,substri));
    return 0;

}
