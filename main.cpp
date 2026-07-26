#include <stdio.h>
#include <unistd.h> // for sysconf
#include <stdlib.h> // for exit()
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h> // for open()

void readCpuStats() {
    // open the /proc/stat file in read-only mode
    int stat_fd = 0;
    stat_fd = open("/proc/stat", O_RDONLY);
    if (stat_fd < 0) {
        printf("can't open /proc/stat\n");
        exit(0);
    }

    off_t offset = lseek(stat_fd, 0, SEEK_CUR);
    if (offset < 0) {
        printf("can't seek to the end of /proc/stat\n");
        exit(0);
    } else {
        printf("offset : %ld\n", offset);
    }
    // read 1st line of /proc/stat 
    char stat_buf[1024 * 2];

    ssize_t bytes_read = read(stat_fd, stat_buf, sizeof(stat_buf));
    if (bytes_read < 0) {
        printf("can't read /proc/stat\n");
        exit(0);
    } else {
        printf("cpu stats : %s\nbytes read : %ld\n", stat_buf, bytes_read);
    }
    // close the file
    if (close(stat_fd) < 0) {
        printf("can't close the file descriptor\n");
        exit(0);
    }
}

int main(){

    long ret_val = sysconf(_SC_NPROCESSORS_ONLN);
    if (ret_val <= 0){
        printf("can't find no. of CPU cores online\n");
        exit(0);
    }

    printf("no. of CPU cores online : %ld\n", ret_val);

    ret_val = sysconf(_SC_NPROCESSORS_CONF);
    if (ret_val <= 0){
        printf("can't find no. of CPU cores configured\n");
        exit(0);
    }

    printf("no. of CPU cores configured : %ld\n", ret_val);

    // Total CPU usage across the system
    /*
    read /proc/stat once and save cpu counters
    sleep for 1000ms and read it again
    
    */
   readCpuStats();

    return 0;
}