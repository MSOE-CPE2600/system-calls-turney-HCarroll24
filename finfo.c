/*************************************************************************
 * @file finfo.c
 * @brief Write program that achieves file information tasks
 *
 * Name: Hunter Carroll
 * Course: CPE 2600
 * Section: 012
 * Assignment: Lab 9
 *
 * compile: make clean, make
 * run: ./finfo
*************************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // Check correct number of arguments given by user
    if (argc != 2) {
        printf("Error: Incorrect number of arguments\n");
        printf("Usage: ./finfo <file_path>\n");
        return 1;
    }

    // Print file information
    struct stat file_info;
    if (stat(argv[1], &file_info) == -1) {
        perror("Error getting file information");
        return 1;
    }
    
    // Figure out file type an dprint
    char file_type[50];
    char permissions[10];
    char time_string[100];
    struct tm *time_info;
    if (S_ISREG(file_info.st_mode)) {
        sprintf(file_type, "Regular File");
    } else if (S_ISDIR(file_info.st_mode)) {
        sprintf(file_type, "Directory");
    } else if (S_ISLNK(file_info.st_mode)) {
        sprintf(file_type, "Symbolic Link");
    } else if (S_ISCHR(file_info.st_mode)) {
        sprintf(file_type, "Character Device");
    } else if (S_ISBLK(file_info.st_mode)) {
        sprintf(file_type, "Block Device");
    } else if (S_ISFIFO(file_info.st_mode)) {
        sprintf(file_type, "FIFO/Pipe");
    } else if (S_ISSOCK(file_info.st_mode)) {
        sprintf(file_type, "Socket");
    } else {
        sprintf(file_type, "Unknown");
    }
    
    // Conver permissions to string
    if (file_info.st_mode & S_IRUSR) {
        permissions[0] = 'r';
    } else {
        permissions[0] = '-';
    }
    if (file_info.st_mode & S_IWUSR) {
        permissions[1] = 'w';
    } else {
        permissions[1] = '-';
    }
    if (file_info.st_mode & S_IXUSR) {
        permissions[2] = 'x';
    } else {
        permissions[2] = '-';
    }
    if (file_info.st_mode & S_IRGRP) {
        permissions[3] = 'r';
    } else {
        permissions[3] = '-';
    }
    if (file_info.st_mode & S_IWGRP) {
        permissions[4] = 'w';
    } else {
        permissions[4] = '-';
    }
    if (file_info.st_mode & S_IXGRP) {
        permissions[5] = 'x';
    } else {
        permissions[5] = '-';
    }
    if (file_info.st_mode & S_IROTH) {
        permissions[6] = 'r';
    } else {
        permissions[6] = '-';
    }
    if (file_info.st_mode & S_IWOTH) {
        permissions[7] = 'w';
    } else {
        permissions[7] = '-';
    }
    if (file_info.st_mode & S_IXOTH) {
        permissions[8] = 'x';
    } else {
        permissions[8] = '-';
    }
    permissions[9] = '\0';

    // Format modification time
    time_info = localtime(&file_info.st_mtime);
    if (time_info == NULL) {
        printf("Error: Could not get last modified time\n");
        return 1;
    }
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

    // Print all information
    printf("File Type: %s\n", file_type);
    printf("Permissions: %s\n", permissions);
    printf("Onwer UID: %d\n", file_info.st_uid);
    printf("File Size: %ld bytes\n", file_info.st_size);
    printf("Last Modified: %s\n", time_string);

    return 0;
}