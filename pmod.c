/*************************************************************************
 * @file pmod.c
 * @brief Write program that modifies its own priority, sleeps for
 * 1837272638 nanoseconds, and prints a goodbye message and exits
 *
 * Name: Hunter Carroll
 * Course: CPE 2600
 * Section: 012
 * Assignment: Lab 9
 *
 * compile: make clean, make
 * run: ./pmod
*************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sched.h>
#include <time.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    // Get the current priority
    int priority = getpriority(PRIO_PROCESS, 0);
    if (priority == -1 && errno != 0) {
        if (errno == ESRCH) {
            printf("Error: Process identifier 0 does not exist\n");
        } else if (errno == EPERM || errno == EACCES) {
            printf("Error: Permission denied accessing process 0\n");
        }
    }

    // Print Current priority
    printf("Current priority: %d\n", priority);

    // Reduce priority by 10
    int new_nice = nice(10);
    if (new_nice == -1 && errno != 0) {
        perror("nice");
        return 1;
    }
    printf("New Priority: %d\n", new_nice);
    
    // Sleep for 1837272638 nanoseconds
    struct timespec sleep_time;
    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 837272638;
    nanosleep(&sleep_time, NULL);

    // Print Goodbye Message
    printf("Goodbye!\n");

    return 0;
}