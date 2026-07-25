#include <stdio.h>
#include <unistd.h> // for sysconf
#include <stdlib.h>

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

    return 0;
}