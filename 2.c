//Prime range
#!/bin/bash

read -p "Enter start (2-x)>> " start
read -p "Enter end (2-x)>> " end

for((i=$start;i<=$end;i++))
do
	flag=0
	for((j=2;j<$i;j++))
	do
		if [ $(( $i%$j )) -eq 0 ]
		then
			flag=1
		fi
	done
	if [ $flag -eq 0 ]
	then
		echo "$i "
	fi
done
//prio-pre
#include <stdio.h>
typedef struct
{
    int id, at, bt, ct, tat, wt, rt, pri;
} Process;
void prioritypscheduling(Process proc[], int n)
{
    int i, f = 0, time = 0, exec = 0, num = n, highp = 99999;
    while (num > 0)
    {
        for (i = 0; i < n; i++)
        {
            if (proc[i].at <= time && proc[i].pri < highp && proc[i].rt > 0)
            {
                highp = proc[i].pri;
                exec = i;
                f = 1;
            }
        }
        if (f == 0)
            time++;
        else
        {
            proc[exec].rt--;
            highp = proc[exec].pri;
            if (proc[exec].rt== 0)
                highp = 99999;
            if (proc[exec].rt == 0)
            {
                proc[exec].ct = time + 1;
                printf("Process-%d completed at %d\n", proc[exec].id, proc[exec].ct);
                proc[exec].tat = proc[exec].ct - proc[exec].at;
                proc[exec].wt = proc[exec].tat - proc[exec].bt;
                proc[exec].rt = 0;
                num--;
            }
            time++;
		  printf("|P%d\t%d",proc[exec].id,time);

        }
    }
}
void printdata(Process processes[], int n)
{
    int wtsum = 0, tatsum = 0;
    printf("P-ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        wtsum += processes[i].wt;
        tatsum += processes[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }
    printf("Average Waiting Time : %.2f\n", (float)wtsum / n);
    printf("Average Turnaround Time : %.2f\n", (float)tatsum / n);
}
int main()
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
        processes[i].rt = processes[i].bt;
        printf("Enter Priority : ");
        scanf("%d", &processes[i].pri);
    }
    prioritypscheduling(processes, n);
    printdata(processes, n);
    return 0;
}
