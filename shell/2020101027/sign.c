#include "signal.h"
#include <stdio.h>
#include <string.h>
#include "jobs.h"
#include <stdlib.h>
extern struct job *car;

void sigc(char **string)
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
    if (string[2] != NULL)
    {
        int signum = atoi(string[2]);
        if (signum <= 0 | signum > 31)
        {
            printf("Give a valid signal");
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
            car->next->RS = 'S';
            car = gosh;
            kill(pid, signum);
        }
    }
    else
    {
        printf("Give sufficient number of args");
        return;
    }
}