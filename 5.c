// 5.a

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
int fd,n;
char buffer[30];
if(argc<2)
{
printf("File name not entered\n");
exit(0);
}
fd=open(argv[1],O_RDWR);
if(fd==-1)
{
printf("Failed to open file\n");
exit(0);
}
printf("Reading first 10 characters from file\n");
n = read(fd,buffer,10);
write(0,buffer,n);
printf("Skipping 5 characters from current position in file\n");
lseek(fd,5,SEEK_CUR);
n = read(fd,buffer,10);
write(0,buffer,n);
printf("Going to 10 characters before current position in file\n");
lseek(fd,-10,SEEK_CUR);
n = read(fd,buffer,10);
write(0,buffer,n);
printf("Reading 5 characters before end position in file\n");
lseek(fd,-5,SEEK_END);
n = read(fd,buffer,10);
write(0,buffer,n);
printf("Going to 3rd character before beginning in file\n");
lseek(fd,3,SEEK_SET);
n = read(fd,buffer,10);
write(0,buffer,n);
}

//FCFS

#include <stdio.h>
typedef struct{
int id;
int at;
int bt;
int ct;
int tat;
int wt;
}Process;
void fcfsscheduling(Process processes[], int n)
{
Process t;
int curt=0;
for (int i=0;i<n;i++)
{
for(int j=0;j<n-i-1;j++)
{
if(processes[j].at>processes[j+1].at)
{
t=processes[j];
processes[j]=processes[j+1];
processes[j+1]=t;
}
}
}
for(int i=0;i<n;i++)
{
if(curt<processes[i].at)
curt=processes[i].at;
printf("Process %d executed from %d to %d time\n",processes[i].id,curt,processes[i].bt+curt);
processes[i].ct=curt+processes[i].bt;
processes[i].tat=processes[i].ct-processes[i].at;
processes[i].wt=processes[i].tat-processes[i].bt;
curt+=processes[i].bt;
}
}
void printdata(Process processes[], int n)
{
Process t;
int wtsum=0,tatsum=0;
printf("P-ID\tAT\tBT\tCT\tTAT\tWT\n");
for (int i=0;i<n;i++)
{
for(int j=0;j<n-i-1;j++)
{
if(processes[j].id>processes[j+1].id)
{
t=processes[j];
processes[j]=processes[j+1];
processes[j+1]=t;
}
}
}
for(int i=0;i<n;i++)
{
wtsum+=processes[i].wt;
tatsum+=processes[i].tat;
printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].id,processes[i].at,processes[i].bt,processes[i].ct,processes[i].tat,processes[i].wt);
}
printf("Average Waiting Time : %f\n",(float)wtsum/n);
printf("Average Turnaround Time : %f\n",(float)tatsum/n);
}
void main()
{
int n;
printf("Enter the number of processes : ");
scanf("%d",&n);
Process processes[n];
for(int i=0;i<n;i++)
{
printf("Process-%d\n",i+1);
processes[i].id=i+1;
printf("Enter the Arrival Time : ");
scanf("%d",&processes[i].at);
printf("Enter the Burst Time : ");
scanf("%d",&processes[i].bt);
}
fcfsscheduling(processes,n);
printdata(processes,n);
}
