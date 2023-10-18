#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

struct pinfo {
    int ppid;
    int syscall_count;
    int page_usage;
};

int main(int argc, char* argv[]){
    struct pinfo info;
    printf("result: %d\n", procinfo(&info));
    printf("ppid: %d, syscall_count: %d, page_usage: %d\n", info.ppid, info.syscall_count, info.page_usage);
    exit(0);
}