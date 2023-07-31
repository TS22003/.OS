// Simulation of "cat" command
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    FILE *fp1;
    char ch;
    if (argc < 2)
    {
        printf("\nYou are not passing the Filename\n");
        exit(1);
    }
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        printf("File doesn't exist\n");
        exit(1);
    }
    while ((ch = fgetc(fp1)) != EOF)
        printf("%c", ch);
    fclose(fp1);
    return 0;
}

// required
// Parent program to print prime numbers in given range using shm_open and mmap system calls.
// Prime child

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i, m, n;
    int flag = 0;
    void *shmptr;
    int shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    shmptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("\nChild Printing:\n");
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    for (i = m; i <= n; i++)
    {
        for (int j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                flag = 1;
            }
        }

        if (flag == 0)
        {
            sprintf(shmptr, "%d ", i);
            printf("%d ", i);
            shmptr += strlen(shmptr);
        }

        flag = 0;
    }

    return 0;
}

// prime parent

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i, m, n;
    int flag = 0;
    const int SIZE = 4096;
    pid_t pid;
    int shm_fd;
    void *shmptr;

    if (argc > 2)
    {
        sscanf(argv[1], "%d", &m);
        sscanf(argv[2], "%d", &n);
        if (m < 1 || n < 1)
        {
            printf("\nWrong input given!!\n");
            return 0;
        }
        else if (m > n)
        {
            int temp = m;
            m = n;
            n = temp;
        }
    }
    else
    {
        printf("\nNo or wrong number of parameters passed in the command line!!\n");
        exit(0);
    }

    pid = fork();
    if (pid == 0)
    {
        // This is the child part
        execlp("./prime", "prime", argv[1], argv[2], NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\n[PARENT] Child process completed\n");
        shm_fd = shm_open("OS", O_RDONLY, 0666);
        shmptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("\nParent printing:\n");
        printf("%s\n", (char *)shmptr);
        shm_unlink("OS");
    }

    return 0;
}

// for compiling:
// cc parent.c -lrt
// cc child.c -o prime -lrt
//  ./a.out 5 89
/*Child Printing:
5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89
[PARENT] Child process completed

Parent printing:
5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89
 */
//  program to print fibonacci numbers using shmget and shmat system calls.
// child

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i, m, n, flag = 0;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666);
    shmptr = shmat(shmid, NULL, 0666);

    printf("\nChild Printing:\n");
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    for (i = m; i <= n; i++)
    {
        for (int j = 2; j <= n / 2; j++)
        {
            if (i % j == 0)
            {
                flag = 1;
            }
        }

        if (flag == 0)
        {
            sprintf(shmptr, "%d ", i);
            printf("%d ", i);
            shmptr += strlen(shmptr);
        }

        flag = 0;
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

// parent
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i, m, n, flag = 0;
    pid_t pid;
    const int SIZE = 4096;
    void *shmptr;
    int shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
    shmptr = shmat(shmid, NULL, 0666);

    if (argc > 2)
    {
        sscanf(argv[1], "%d", &m);
        sscanf(argv[2], "%d", &n);
        if (m < 1 || n < 1)
        {
            printf("\nWrong input is passed:\n");
            return 0;
        }
        else if (m > n)
        {
            int temp = m;
            m = n;
            n = temp;
        }
    }
    else
    {
        printf("\nWrong number of parameters passed in the command line\n");
        return 1;
    }

    pid = fork();
    if (pid == 0)
    {
        // This is the child process part
        execlp("./prime", "prime", argv[1], argv[2], NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\n[PARENT] Child completed\n");
        printf("\nParent printing:\n");
        printf("%s\n", (char *)shmptr);
        shmdt(shmptr);
    }

    return 0;
}
