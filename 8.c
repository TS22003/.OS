//Simulation of "ls" command 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
void main(int argc, char *argv[])
{
DIR *dp;
struct dirent *dirp;
if(argc<2)
{
printf("\nYou are not passing Directory\n");
exit(1);
}
if((dp=opendir(argv[1]))==NULL)
{
printf("Directory doesn't exist\n");
exit(1);
}
while((dirp=readdir(dp))!=NULL)
printf("%s\n",dirp->d_name);
closedir(dp);
}

