#include "fg.h"
#include <stdio.h>
#include "jobs.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
extern struct job *car;

void fgc(char **string)
{
    if (string[1] == NULL)
    {
        printf("Give sufficient number of args");
        return;
    }
    int number = atoi(string[1]);
    if (number == 0)
    {
        printf("Give a valid number");
        return;
    }
    int pid = -1;
    struct job *gosh = car;
    while (car->next != NULL)
    {
        if (car->next->num == number)
        {
            pid = car->next->pid;
            break;
        }
        car = car->next;
    }

    if (pid == -1)
    {
        printf("Give a valid number seems wrong");
        car = gosh;
        return;
    }
    else
    {

        car->next->RS = 'R';
        car = gosh;
        int pid1 = fork();
        if (pid1 == 0)
        {
            kill(pid, SIGSTOP);
            kill(pid, SIGCONT);
            pause();
        }
        if (pid1 > 0)
        {
            wait(0);
        }
    }
}