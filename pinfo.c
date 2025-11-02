/*************************************************************************
 * @file pinfo.c
 * @brief Write program that achieves system information tasks
 *
 * Name: Hunter Carroll
 * Course: CPE 2600
 * Section: 012
 * Assignment: Lab 9
 *
 * compile: make clean, make
 * run: ./pinfo
*************************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sched.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int priority;
    int scheduler;

    // check if correct pid given by user
    if (argc == 1) {
        pid = getpid();
    } else {
        pid = atoi(argv[1]);
        if (pid <= 0) {
            printf("Error: Invalid PID\n");
            return 1;
        }
    }

    // Try to get the scheduler - will fail if doesn't exist
    scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        if (errno == ESRCH) {
            printf("Error: PID %d does not exist\n", pid);
        } else if (errno == EPERM){
            printf("Error: permission denied accessing process %d\n", pid);
        } else {
            perror("Error getting scheduler");
        }
        return 1;
    }

    // Get the priority
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        if (errno == ESRCH) {
            printf("Error: Process identifier %d does not exist\n", pid);
        } else if (errno == EPERM || errno == EACCES) {
            printf("Error: Permission denied accessing process %d\n", pid);
        } else {
            perror("Error getting priority");
        }
        return 1;
    }

    // Print out the results
    printf("Process Priority %d\n", priority);

    // Convert scheduler number to string
    if (scheduler == SCHED_OTHER) {
        printf("Scheduling Method: SCHED_OTHER\n");
    } else if (scheduler == SCHED_FIFO) {
        printf("Scheduling Method: SCHED_FIFO\n");
    } else if (scheduler == SCHED_RR) {
        printf("Scheduling Method: SCHED_RR\n");
    } else if (scheduler == SCHED_BATCH) {
        printf("Scheduling Method: SCHED_BATCH\n");
    } else if (scheduler == SCHED_IDLE) {
        printf("Scheduling Method: SCHED_IDLE\n");
    } else {
        printf("Scheduling Method: UNKNOWN\n");
    }
    
    
    return 0;
}