#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

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

//part1

uint64 sys_sysinfo(void){
  int n;
  argint(0, &n);
  return print_sysinfo(n);
}

//part2

uint64 sys_procinfo(void){
  uint64 ptr;
  argaddr(0, &ptr);
  struct proc* p = myproc();

  uint32 data[3];
  //1. get ppid
  data[0] = p->parent->pid;
  //2. get syscall_count
  data[1] = p->syscall_count_of_this_process - 1; // The -1 operation excludes this syscall
  //3. get page_usage
  int page_count = p->sz / 4096;  //page size in xv6 is 4KB
  if(p->sz % 4096 != 0) page_count++; //ceil(p->sz / 4096)
  data[2] = page_count; 

  return copyout(p->pagetable, ptr, (char*)data, sizeof(uint32) * 3); //copy the data to user space and return
}