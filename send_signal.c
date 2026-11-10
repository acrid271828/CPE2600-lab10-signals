/**************
* send_signal.c
* Alex Grant
* 11/10/2026
* sends SIGUSR1 with a random number to a downstream process
* to compile: $ make send
* Run with the pid to send the signal to as a command-line arg
**************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("usage: ./send <pid>");
        exit(1);
    }

    int dest = atoi(argv[1]);
    if (dest <= 0){
        printf("invalid pid\n");
        exit(1);
    }

    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    srand(time.tv_nsec);

    int sends = 10;
    while(sends-- > 0){
        union sigval data = {
            .sival_int = rand(),
        };
        printf("Sending %d to downstream process\n", data.sival_int);
        sigqueue(dest, SIGUSR1, data);
        sleep(1);
    }
}