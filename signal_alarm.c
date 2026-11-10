/**************
* signal_alarm.c
* Alex Grant
* 11/10/2026
* sends itself a SIGALRM
* to compile: $ make alarm
**************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_alarm(int sig){
    printf("Just five more minutes please\n");
    exit(1);
}

int main(){

    signal(SIGALRM, handle_alarm);

    alarm(5);

    while(1){
        printf("zzz\n");
        sleep(1);
    }

    return 0;
}