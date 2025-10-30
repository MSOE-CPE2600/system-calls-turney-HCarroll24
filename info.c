/*************************************************************************
 * @file info.c
 * @brief Write program that achieves system information tasks
 *
 * Name: Hunter Carroll
 * Course: CPE 2600
 * Section: 012
 * Assignment: Lab 9
 *
 * compile: make clean, make
 * run: ./info
*************************************************************************/
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    // Current time of day in nanoseconds
    struct timespec current;

    clock_gettime(CLOCK_REALTIME, &current);

    // Conversion to day
    time_t seconds = current.tv_sec;
    struct tm *info = localtime(&seconds);

    char buffer[26];
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", info);
    printf("Current local time: %s\n", buffer);

    return 0;
}