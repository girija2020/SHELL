#include "pinf.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

extern char* homedir;

void pinfo(char **string)
{
    pid_t x = getpid();
    gid_t p = getgid();
    if (string[1] != NULL)
    {
        x = atoi(string[1]);
    }
    printf("pid -- %d\n", x);
    char fn[2000], fn1[2000];
    sprintf(fn, "/proc/%d/stat", x);
    FILE *fd = fopen(fn, "r");
    if (fd == NULL)
    {
        perror("Are you sure it is Wingaardium Leviossa. Maybe try Wingardium Leviosa");
        return;
    }
    int pid, ppid, dummy, pgrp;
    char *name;
    char state;
    unsigned dum, tpgrp;
    unsigned long dumm;
    long du;
    long long int d;
    fscanf(fd, "%d %s %c %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %ld *", &pid, &name, &state, &ppid, &pgrp, &dummy, &dummy, &tpgrp, &dumm, &dumm, &dumm, &dumm, &dumm, &dumm, &du, &du, &du, &du, &du, &du, &d, &du);
    printf("Process State: %c", state);
    if (pid == tpgrp)
    {
        printf("+\n");
    }
    else
    {
        printf("\n");
    }
    printf("Memory: %ld {Virtual Memory}\n", du);
    fflush(stdin);
    fflush(stdout);
    fclose(fd);
    for (int i = 0; i < 2000; i++)
    {
        fn1[i] = '\0';
    }
    sprintf(fn, "/proc/%d/exe", pid);
    int fd1 = open(fn, O_RDONLY);
    if (fd1 < 0)
    {
        perror("");
        return;
    }
    readlink(fn, fn1, 1999);
    int len = strlen(homedir);
    int l = 1;

    for (int i = 0; i < len; i++)
    {
        if (fn1[i] != homedir[i])
        {
            l = 0;
            break;
        }
    }
    int q = strlen(fn1);
    if (l == 1)
    {
        if (q - len != 0)
        {
            for (int i = 0; i < q - len; i++)
            {
                fn1[i] = fn1[i + len];
            }
            for (int i = q - len; i < q; i++)
            {
                fn1[i] = '\0';
            }
        }
        else
        {
            for(int i=0;i<2000;i++)
            {
                fn1[i] = '\0';
            }
        }
    }


    char names[1000] = "";

    if (l == 1)
    {
        strcat(names, "~");
        if (q - len != 0)
        {
            strcat(names, fn1);
        }
    }
    else
    {
        strcpy(names,fn1);
    }
    printf("Executable Path: %s\n", names);
    close(fd1);
}