#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

struct pinfo {
    int ppid;
    int syscall_count;
    int page_usage;
};

int main(int argc, char* argv[]){
    // int n = 0;
    // if(argc >= 2)
    //     n = atoi(argv[1]);

    // printf("%d\n", sysinfo(n));
    // exit(0);

    struct pinfo info;
    int result = procinfo(&info);
    printf("result: %d\n", result);
    printf("ppid: %d, syscall count: %d, page_usage: %d\n", info.ppid, info.syscall_count, info.page_usage);

    exit(0);
}