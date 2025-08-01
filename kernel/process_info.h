#define MAX_NAME_LEN 16
#define MAX_PROCESSES 64

struct process_info {
  int pid;
  int state;
  int ticks;
  char name[MAX_NAME_LEN];
};
