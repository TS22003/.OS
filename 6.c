//zombie
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
pid_t my_pid, parent_id, child_pid, wid;
int i=5;
child_pid = fork();
if(child_pid<0)
{
printf("Fork Failed\n");
exit(0);
}
if(child_pid==0)
{
printf("[CHILD] This is Child Process\n");
my_pid = getpid();
parent_id = getppid();
printf("[CHILD] My PID = %d\n",my_pid);
printf("[CHILD] My Parent's PID = %d\n",parent_id);
exit(0);
}
else
{
printf("[PARENT] This is Parent Process\n");
my_pid = getpid();
parent_id = getppid();
printf("[PARENT] My PID = %d\n",my_pid);
printf("[PARENT] My Parent's PID = %d\n",parent_id);
printf("[PARENT] Sleeping for 10 seconds\n");
sleep(10);
printf("[PARENT] My Child's PID = %d has ended, but its entry is in the Process table\n",child_pid);
execlp("/bin/ps","ps",NULL);
}
return 0;
}

//orphan
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
pid_t my_pid, parent_id, child_pid, wid;
int i=5;
child_pid = fork();
if(child_pid<0)
{
printf("Fork Failed\n");
exit(0);
}
if(child_pid==0)
{
printf("[CHILD] This is Child Process\n");
my_pid = getpid();
parent_id = getppid();
printf("[CHILD] My PID = %d\n",my_pid);
printf("[CHILD] My Parent's PID = %d\n",parent_id);
printf("[CHILD] Sleeping for 10 seconds\n");
sleep(5);
printf("[CHILD] Parent Process exited so Child Process is Orphan\n");
exit(0);
}
else
{
printf("[PARENT] This is Parent Process\n");
my_pid = getpid();
parent_id = getppid();
printf("[PARENT] My PID = %d\n",my_pid);
printf("[PARENT] My Parent's PID = %d\n",parent_id);
exit(0);
}
return 0;
}
