//Simulation of "grep" command 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
FILE *fp;
char ch,temp[100];
if(argc<3)
{
printf("\nYou are not passing the Filename\n");
exit(1);
}
fp=fopen(argv[2],"r");
if(fp==NULL)
{
printf("File doesn't exist\n");
exit(1);
}
while(!feof(fp))
{
fgets(temp,100,fp);
if(strstr(temp,argv[1]))
{
printf("%s",temp);
break;
}
}
fclose(fp);
return 0;
}
