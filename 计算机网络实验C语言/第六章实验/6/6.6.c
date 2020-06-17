#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int MSS = 1024;
int Threshold = 32768;
int TriACKRound=16;
int TimeoutRound=22;
int EndRound=26;

int main(){
    int cwnd=1024;
    printf("MSS: %d, ThresholdL %d\n",MSS,Threshold);
    char data[1024]="this is a test for TCP congestion control.";
    int increase_mode=0;
    for(int i=1;i<=EndRound;i++){
        if(i==TriACKRound){
            cwnd/=2;
            Threshold/=2;
            increase_mode=0;
        }else if(i==TimeoutRound){
            cwnd/=2;
            Threshold/=2;
            increase_mode=0;
        }else if(i==EndRound){

        }else{
            if(cwnd<=Threshold&&increase_mode==0){
                cwnd*=2;
            }else if(cwnd==Threshold*2&&increase_mode==0){
                cwnd/=2;
                increase_mode=1;
            }else{
                cwnd+=1;
            }
        }
        printf("round: %d, cwnd: %d, data: %s\n",i,cwnd,data);
    }

}