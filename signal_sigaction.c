/**************
* signal_sigaction.c
* Alex Grant
* 11/10/2026
* waits for SIGUSR1 and prints the sigaction data
* to compile: $ make sigaction
* From a different terminal, run `kill -SIGUSR1 <pid>`, where pid is what was printed by this program
**************/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig, siginfo_t* info, void* content){
    printf("Received signal from process %d\n", info->si_pid);
}


int main(){
    struct sigaction action = {
        .sa_flags = SA_SIGINFO,
        .sa_sigaction = handle_sigusr1,
    };
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);

    printf("process %d has started. Waiting for signals...\n", getpid());

    while(1){
        sleep(1);
    }
}