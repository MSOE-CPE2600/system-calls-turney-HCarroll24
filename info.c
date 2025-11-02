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
#define _POSIX_C_SOURCE 199309L

#include <time.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    // Current time of day in nanoseconds
    struct timespec ts;
    struct tm *local_time;
    time_t seconds_since_midnight;

    clock_gettime(CLOCK_REALTIME, &ts);
    local_time = localtime(&ts.tv_sec);
    seconds_since_midnight = local_time->tm_hour*3600 + local_time->tm_min*60 + local_time->tm_sec;
    printf("%-*s : %lu.%lu\n", 30, "1. Time of day", seconds_since_midnight, ts.tv_nsec);

    // Systems Network Name
    struct utsname u;
    if (uname(&u) == -1) {
        perror("uname");
        return 1;
    }
    printf("%-*s : %s\n", 30, "2. System Network Name", u.nodename);

    // Operating System's Name
    printf("%-*s : %s\n", 30, "3. Operating System's Name", u.sysname);

    // Operating System's Release and Version
    printf("%-*s : %s\n", 30, "4. Operating System's Release", u.release);
    printf("%-*s : %s\n", 30, "5. Operating System's Version", u.version);

    // System's Hardware Type
    printf("%-*s : %s\n", 30, "6. System's Hardware Type", u.machine);

    // Number of CPUs
    int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    printf("%-*s : %d\n", 30, "7. Number of CPUs", num_cpus);

    // Total Memory Physical (Bytes)
    struct sysinfo info;
    if (sysinfo(&info) == -1) {
        perror("sysinfo");
        return 1;
    }
    printf("%-*s : %lu bytes\n", 30, "8. Total Memory Physical", info.totalram * info.mem_unit);

    // Total Amount of Free Memory (Bytes)
    printf("%-*s : %lu bytes\n", 30, "9. Total Free Memory", info.freeram);

    return 0;
}