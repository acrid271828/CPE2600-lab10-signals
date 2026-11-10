
/**
* @file signal_segfault.c
* @brief Program that dereferences a null pointer causing a segmentation fault
*/
/**
* Modified by: Alex Grant
*
* Brief summary of modifications: add handler for SIGSEGV
* Causes an infinite loop of "Received seg fault" printing in the terminal because *i is repeatedly called
*/
#include <stdio.h>
#include <signal.h>

void handle_segfault(int sig){
    printf("Received seg fault\n");
}
int main (int argc, char* argv[]) {

    signal(SIGSEGV, handle_segfault);
    // Declare a null pointer
    int* i = NULL;
    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);
    // Return to exit the program
    return 0;
}
