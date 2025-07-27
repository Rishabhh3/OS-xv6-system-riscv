#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#define MAX_PROCESSES 64

struct process_info {
  int pid;
  int state;
  int ticks;
  char name[16];
};

#endif
