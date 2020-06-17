#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd!=-1);
    struct sockaddr_in ser,cli;
    memset(&ser,0,sizeof(ser));
    
    ser.sin_family=AF_INET;
    ser.sin_port=htons(6000);
    ser.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    int res=bind(sockfd,(struct sockaddr*)&ser,sizeof(ser));
    //assetr(res!=-1);
    
    listen(sockfd,5);
    
    while(1)
    {
        int len=sizeof(cli);
        int c=accept(sockfd,(struct sockaddr*)&cli,&len);
        if(c<0)
        {
            perror("error\n");
            continue;
        }
        while(1)
        {
            char recvbuf[128]={0};
            int n=recv(c,recvbuf,127,0);
            if(n<=0)
            {
                printf("one client over\n");
                break;
            }
            printf("%d:%s\n",c,recvbuf);
            for(int i=0;i<strlen(recvbuf);i++){
                recvbuf[i] = recvbuf[i] - 32;
            }
            send(c,recvbuf,strlen(recvbuf),0);
        }
        close(c);
    }
    close(sockfd);
}

