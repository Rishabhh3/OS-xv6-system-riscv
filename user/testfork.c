#include "kernel/types.h"
#include "user/user.h"

int main(){
	int pid = fork();
	if(pid == 0){
		printf("Child process, PID = %d\n", getpid());
		exit(0);
	}else{
		wait(0);
		printf("Parent Process, PID = %d\n", getpid());
	}
	exit(0);
}
