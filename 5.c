// 5.a

// to demonstrate the use of I/O system calls for file I/O( read, write, open, lseek)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFFER_SIZE 30
int main()
{
  int fd, n;
  char buffer[BUFFER_SIZE];
  fd = open("file.c", O_RDWR);

  if (fd == -1)
  {
    printf("Failed to open file.\n");
    exit(0);
  }
  printf("Reading first 10 characters from file: \n");
  n = read(fd, buffer, 10);
  write(1, buffer, n);

  printf("\nSkipping 5 characters from current position in the file: \n");
  lseek(fd, 5, SEEK_CUR);
  n = read(fd, buffer, 10);
  write(1, buffer, n);
  printf("\nGoing 10 characters before the current position in the file: \n");
  lseek(fd, -10, SEEK_CUR);
  n = read(fd, buffer, 10);
  write(1, buffer, n);
  printf("\nGoing to 5th last character in the file: \n");
  lseek(fd, -5, SEEK_END);
  n = read(fd, buffer, 7);
  write(1, buffer, 5);
  printf("\nGoing to the 3rd character in the file: \n");
  lseek(fd, 3, SEEK_SET);
  n = read(fd, buffer, 5);
  write(1, buffer, n);
  return 0;
}

// FCFS
#include <stdio.h>
typedef struct
{
  int id;
  int at;
  int bt;
  int ct;
  int tat;
  int wt;
} Process;
void fcfsscheduling(Process processes[], int n)
{
  Process t;
  int curt = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (processes[j].at > processes[j + 1].at)
      {
        t = processes[j];
        processes[j] = processes[j + 1];
        processes[j + 1] = t;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (curt < processes[i].at)
      curt = processes[i].at;
    printf("Process %d executed from %d to %d time\n", processes[i].id, curt, processes[i].bt + curt);
    processes[i].ct = curt + processes[i].bt;
    processes[i].tat = processes[i].ct - processes[i].at;
    processes[i].wt = processes[i].tat - processes[i].bt;
    curt += processes[i].bt;
  }
  printf("Gannt CHart is:\n");
  for (int i = 0; i < n; i++)
  {
    printf("|P%d %d\t", processes[i].id, processes[i].bt);
  }
}
void printdata(Process processes[], int n)
{
  Process t;
  int wtsum = 0, tatsum = 0;
  printf("\n");
  printf("P-ID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (processes[j].id > processes[j + 1].id)
      {
        t = processes[j];
        processes[j] = processes[j + 1];
        processes[j + 1] = t;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    wtsum += processes[i].wt;
    tatsum += processes[i].tat;
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
  }
  printf("Average Waiting Time : %f\n", (float)wtsum / n);
  printf("Average Turnaround Time : %f\n", (float)tatsum / n);
}
void main()
{
  int n;
  printf("Enter the number of processes : ");
  scanf("%d", &n);
  Process processes[n];
  for (int i = 0; i < n; i++)
  {
    printf("Process-%d\n", i + 1);
    processes[i].id = i + 1;
    printf("Enter the Arrival Time : ");
    scanf("%d", &processes[i].at);
    printf("Enter the Burst Time : ");
    scanf("%d", &processes[i].bt);
  }
  fcfsscheduling(processes, n);
  printdata(processes, n);
}
