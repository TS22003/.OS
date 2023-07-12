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
