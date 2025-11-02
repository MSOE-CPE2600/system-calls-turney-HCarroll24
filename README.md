# system-calls
These files contain the information and instructions for Lab 9 for CPE 2600 012.

## info.c
Displays general system information about Linux System
 * Current time of day in nanoseconds
 * System network name (hostname)
 * Operating System Name
 * operating system release and version
 * hardware type
 * number of CPUs
 * total physical memory (bytes)
 * total free memory (bytes)

## pinfo.c
Displays process information for specified process id
 * Process priority (nice value)
 * scheduling method

## pmod.c
Modifies the priority of the current process and then sleeps.
 1. Gets and displays current priority
 2. Reduces priority by 10
 3. Displays the new priority
 4. Sleeps for 1837272638 nanoseconds
 5. Prints goodbye message

## finfo.c
Displays detailed information about specified file
 * File type
 * File permissions
 * Owner UID
 * File size
 * Last modification date and time