/**
* @file signal_handler.c
* @brief Sets a signal handler for SIGINT, the handler prints a message and then
quits
*/
/**
* Modified by: Alex Grant
*
* Brief summary of modifications: Print the pid, add a parameter to handle_signal so it doesn't error, and remove the exit() call in the handler
* How to trigger the signal handler:
*  1. From the running program, hit ctrl+c
*  2. From a different terminal, run `kill -SIGINT <pid>`, where pid is what was printed by this program
* When the signal handler is triggered, the program prints "Received a signal" and continues the sleep loop.
* To kill the process, run `kill <pid>` (defaults to SIGKILL). The process will print "Terminated" and exit
*/
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/**
* @brief Signal handler for SIGINT - prints a message and exits
*/
void handle_signal(int sig) {
    printf("Received a signal\n");
}
int main() {
    // Register for the signal
    signal(SIGINT, handle_signal);

    printf("Process %d is running...\n", getpid());
    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }
    return 0;
}