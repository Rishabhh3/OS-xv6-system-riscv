#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define  MAX_PROCESSES 64

char *states[] = {
    "UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"
};

int
main()
{
    struct process_info infos[MAX_PROCESSES];
    
    if(top(infos) < 0){
        printf("top: syscall failed\n");
        exit(1);
    }

    printf("PID\tSTATE\t\tTICKS\tNAME\n");
    for(int i = 0; i < MAX_PROCESSES; i++){
        if(infos[i].pid == 0)   continue;

        printf("%d\t%s\t%d\t%s\n",
        infos[i].pid,
        states[infos[i].state],
        infos[i].ticks,
        infos[i].name);
    }
    exit (0);
}