#include "kernel/types.h"
#include "user/user.h"

int main(){
	int pid = getpid();
	printf("My PID is: %d\n", pid);
	exit(0);
}
