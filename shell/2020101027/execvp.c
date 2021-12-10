#include <stdio.h>
#include "execvp.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "jobs.h"
#include <sys/mman.h>
#include <signal.h>
#include "pinf.h"
#include <fcntl.h>
extern struct job *jo;
extern struct job *car;
char *q;
int o;
int x;

void sigfore()
{
    kill(getpid(), 0);
}

void sigh()
{
    kill(getpid(), SIGSTOP);
}

void sigfunc()
{
    int num;
    struct job *car = jo;
    while (jo->next != NULL)
    {
        num = jo->next->num;
        jo = jo->next;
    }
    jo->next = malloc(sizeof(struct job));
    jo->next = (struct job *)mmap(NULL, sizeof *jo, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    jo->next->pid = getpid();
    jo->next->RS = 'S';
    strcpy(jo->next->name, q);
    jo->next->num = num++;
    jo = car;
    int x = getpid();
    raise(SIGTSTP);
}

void exec(char **whatstring)
{
    int b = 0;
    int i = 0;
    while (whatstring[i] != NULL)
    {
        if (strcmp(whatstring[i], "&") == 0)
        {
            b = 1;
            break;
        }
        i++;
    }
    q = whatstring[0];
    if (b == 0)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            signal(SIGINT, sigfore);
            signal(SIGTSTP, sigfunc);
            execvp(whatstring[0], whatstring);
            perror("That's not a spell");
            exit(0);
        }
        else if (pid > 0)
        {
            int q = wait(0);
            return;
        }
    }

    else if (b == 1)
    {
        int num = jo->num;
        struct job *what;
        while (jo->next != NULL)
        {
            num = jo->next->num;
            jo = jo->next;
        }
        jo->next = malloc(sizeof(struct job));
        jo->next = (struct job *)mmap(NULL, sizeof *jo, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        int pid1 = fork();
        if (pid1 == 0)
        {
            int z = getpid();
            pid_t pid = fork();
            char *str[10];
            for (int i = 0; i < 10; i++)
            {
                str[i] = NULL;
            }
            int j = 0;
            int k = 0;
            while (k < i)
            {
                if (strcmp(whatstring[k], "&") != 0)
                {
                    str[j] = whatstring[k];
                    j++;
                }
                k++;
            }
            str[j] = NULL;
            int x;
            if (pid == 0)
            {
                z = getpid();
                jo->next->pid = getpid();
                printf("%d\n", z);
                fflush(stdin);
                fflush(stdout);
                for (int o = 0; o < 100; o++)
                {
                    jo->next->name[o] = '\0';
                }
                strcpy(jo->next->name, str[0]);
                jo->next->RS = 'R';
                jo->next->num = num + 1;
                jo->next->next = NULL;
                int u =0;
                if (strcmp("vim", whatstring[0]) == 0 | strcmp("vi", whatstring[0]) == 0 | strcmp("nano", whatstring[0]) == 0 | strcmp("cat", whatstring[0]) == 0)
                {
                    u = 1;
                    jo->next->RS = 'S';
                    jo = what;
                    kill(z, SIGSTOP);
                }
                jo = what;
                printf("%d",atoi(whatstring[1]));
                execvp(str[0], str);
                perror("That's not a spell");
                exit(0);
            }
            else if (pid > 0)
            {
                int wstatus;
                int q = wait(0);
                if (WIFEXITED(0) > 0)
                    printf("%s with pid %d exited normally\n", str[0], q);
                else
                    printf("%s with pid %d exited abnormally\n", str[0], q);
                fflush(stdin);
                fflush(stdout);
                int y = 0;
                while (jo->next != NULL)
                {

                    if (jo->next->pid == q)
                    {
                        jo->next = jo->next->next;
                        if (jo->next != NULL)
                        {
                            y = 1;
                            jo->next->num--;
                        }
                        else
                        {
                            break;
                        }

                        if (jo->next != NULL & y == 1)
                        {
                            jo->next->num--;
                        }
                        jo = jo->next;
                    }
                }
                kill(x, 0);
                kill(z, 0);
                exit(0);
            }
            else if (pid < 0)
            {
                printf("Forking error!");
                return;
            }
        }
        if (pid1 > 0)
        {
            x = 0;
            return;
        }
        if (pid1 < 0)
        {
            printf("Forking error!");
        }
    }
}
