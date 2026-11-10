/**************
* tennis_player.c
* Alex Grant
* 11/10/2026
* passes a ball back-and-forth with another tennis player until the game ends
* to compile: $ make tennis_player
**************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#define SLEEP_TIME 1

typedef struct {
    int is_serving;
    int other_player;
    int my_score;
    int other_score;
} PlayerData;

static volatile PlayerData player_data = {
    .is_serving = -1,
};

static void score(int has_won_point){
    if (has_won_point){
        player_data.my_score++;
    } else {
        player_data.other_score++;
    }
    if (player_data.my_score >= 4 || player_data.other_score >= 4) {
        int delta = player_data.my_score - player_data.other_score;
        if (delta >= 2){
            printf("I WON!!!\n");
            exit(1);
        } else if (delta <= -2){
            printf("aww I lost :(\n");
            exit(1);
        }
    }
}

static void print_points(int points){
    switch (points){
        case(0):
            printf("Love");
            break;
        case(1):
            printf("15");
            break;
        case(2):
            printf("30");
            break;
        case(3):
            printf("40");
            break;
    }
}

static void serve(){
    union sigval info = {
        .sival_int = 1, // always make serve in
    };
    if (player_data.my_score >= 3 && player_data.other_score >= 3){
        // 40-40 and above
        switch(player_data.my_score - player_data.other_score){
            case(1):
                printf("Ad in\n");
                break;
            case(0):
                printf("Deuce\n");
                break;
            case(-1):
                printf("Ad out\n");
                break;
        }
    } else {
        if (player_data.my_score == player_data.other_score){
            print_points(player_data.my_score);
            printf(" all\n");
        } else {
            print_points(player_data.my_score);
            printf("-");
            print_points(player_data.other_score);
            printf("\n");
        }
    }
    sleep(SLEEP_TIME);
    printf("Serving the ball\n");
    sigqueue(player_data.other_player, SIGUSR1, info);
}

static void return_ball(int sig, siginfo_t* info, void* content){
    // first serve in a game
    if (player_data.is_serving == -1){
        printf("N/A\n");
        printf("\n----------\n\n\n\n");
        player_data.is_serving = 0;
        player_data.other_player = info->si_pid;
    }

    // other player missed
    if (!info->si_value.sival_int){
        printf("Out!\n\n----------\n\n");
        score(1); // win point
        if (player_data.is_serving){
            // padding so the text lines up with the server's windows
            serve();
        } else {
            printf("\n\n");
        }
    } else {

        sleep(SLEEP_TIME);

        // return back with 4/5 success rate
        union sigval return_info = {
            .sival_int = rand() > (RAND_MAX / 5),
        };
        printf("Hitting the ball %s\n", return_info.sival_int ? "back" : "out");
        sigqueue(player_data.other_player, SIGUSR1, return_info);

        // failed to return
        if (!return_info.sival_int){
            printf("\n----------\n\n");
            score(0); // lose point
            if (player_data.is_serving){
                serve();
            } else {
                // padding so the text lines up with the server's windows
                printf("\n\n");
            }
        }
    }
}

int main(){
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    srand(time.tv_nsec);

    struct sigaction action = {
        .sa_flags = SA_SIGINFO,
        .sa_sigaction = return_ball,
    };
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);

    printf("Player %d is ready to play. Enter another player to have this one serve to them: ", getpid());

    char buffer[120];
    fgets(buffer, 120, stdin);
    if (player_data.is_serving == -1){
        printf("\n----------\n\n");
        player_data.is_serving = 1;
        player_data.other_player = atoi(buffer);
        serve();
    }

    while(1){
        sleep(1);
    }

    return 0;
}