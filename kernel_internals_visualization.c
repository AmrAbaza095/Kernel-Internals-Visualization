#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_cpu_info() {
    FILE *fp;
    char line[256];
    unsigned long long int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;

    // Open the /proc/stat file to read CPU information
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the first line of the file which contains CPU stats
    if (fgets(line, sizeof(line), fp) != NULL) {
        // Parse the data
        if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", 
                   &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
            
            // Calculate total time and CPU usage percentages
            unsigned long long int total = user + nice + system + idle + iowait + irq + softirq + steal;
            unsigned long long int total_idle = idle + iowait;
            unsigned long long int total_non_idle = total - total_idle;

            float cpu_usage = (float) total_non_idle / total * 100.0;

            printf("CPU Stats:\n");
            printf("User Time: %llu\n", user);
            printf("Nice Time: %llu\n", nice);
            printf("System Time: %llu\n", system);
            printf("Idle Time: %llu\n", idle);
            printf("I/O Wait Time: %llu\n", iowait);
            printf("IRQ Time: %llu\n", irq);
            printf("SoftIRQ Time: %llu\n", softirq);
            printf("Steal Time: %llu\n", steal);
            printf("Guest Time: %llu\n", guest);
            printf("Guest Nice Time: %llu\n", guest_nice);
            printf("Total CPU Time: %llu\n", total);
            printf("Non-Idle Time: %llu\n", total_non_idle);
            printf("CPU Usage: %.2f%%\n", cpu_usage);
        } else {
            printf("Failed to parse CPU stats\n");
        }
    } else {
        printf("Failed to read /proc/stat\n");
    }

    fclose(fp);
}

void read_memory_info() {
    FILE *fp;
    char line[256];
    unsigned long total, free, available;

    // Open the /proc/meminfo file to read memory information
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read memory stats
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "MemTotal") != NULL) {
            sscanf(line, "MemTotal: %lu kB", &total);
        } else if (strstr(line, "MemFree") != NULL) {
            sscanf(line, "MemFree: %lu kB", &free);
        } else if (strstr(line, "MemAvailable") != NULL) {
            sscanf(line, "MemAvailable: %lu kB", &available);
        }
    }

    printf("\nMemory Stats:\n");
    printf("Total Memory: %lu kB\n", total);
    printf("Free Memory: %lu kB\n", free);
    printf("Available Memory: %lu kB\n", available);

    fclose(fp);
}

void read_task_info() {
    FILE *fp;
    char line[256];
    char task_name[256];
    int pid, ppid;

    // Open the /proc directory to read information about each task
    printf("\nTask Details:\n");
    fp = fopen("/proc/loadavg", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the load average (representing task activity)
    if (fgets(line, sizeof(line), fp) != NULL) {
        printf("Load Average: %s", line);
    }

    fclose(fp);
}

int main() {
    printf("Reading CPU Information...\n");
    read_cpu_info();
    
    printf("\nReading Memory Information...\n");
    read_memory_info();
    
    printf("\nReading Task Information...\n");
    read_task_info();

    return 0;
}
