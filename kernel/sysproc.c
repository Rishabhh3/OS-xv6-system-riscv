#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "process_info.h"

extern struct proc proc[NPROC];
extern struct spinlock proc_lock;


uint64
sys_top(void)
{
  uint64 addr;
  if (argaddr(0, &addr) < 0)
    return -1;

  struct process_info infos[MAX_PROCESSES];  //  Declare the array here
  int count = 0;

  acquire(&proc_lock);
  for (struct proc *p = proc; p < &proc[NPROC]; p++) {
   if (p->state != UNUSED) {
    infos[count].pid = p->pid;
    infos[count].state = p->state;
    infos[count].ticks = p->rtime;
    safestrcpy(infos[count].name, p->name, sizeof(p->name));
    count++;
    if (count >= MAX_PROCESSES) break;
  }
}
release(&proc_lock);


  if (copyout(myproc()->pagetable, addr, (char *)infos, count * sizeof(struct process_info)) < 0)
    return -1;

  return count;  // return number of valid entries
}


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
