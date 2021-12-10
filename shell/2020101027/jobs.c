#include "jobs.h"
#include <stdio.h>
#include <execvp.h>
#include <parse.h>
#include <stdlib.h>
#include <string.h>
struct job *jo;
struct job *car;
struct job cat[10];
struct job temp;

void sort()
{
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i <= 9; ++i)
        {
            if (cat[i].num != -1 & strcmp(cat[i].name, cat[i + 1].name) > 0)
            {
                temp = cat[i];
                cat[i] = cat[i + 1];
                cat[i + 1] = temp;
            }
            if (cat[i].num == -1)
            {
                i = 9;
            }
        }
    }
    int i = 0;
    while (cat[i].num != -1 & cat[i].RS == 'R')
    {
        printf("%d Running %s %d\n", cat[i].num, cat[i].name, cat[i].pid);
        i++;
    }
    while (cat[i].num != -1 & cat[i].RS == 'S')
    {
        printf("%d Stopped %s %d\n", cat[i].num, cat[i].name, cat[i].pid);
        i++;
    }
}

void jobsdispr()
{
    struct job *gosh;
    gosh = car;
    int i = 0;
    while (car->next != NULL)
    {
        if (car->next->RS = 'R')
        {
            cat[i] = *(car->next);
            i++;
        }
        car = car->next;
    }
    for (int j = i; j < 10; j++)
        cat[i].num = -1;
    sort();
    car = gosh;
}

void jobsdisps()
{
    struct job *gosh;
    gosh = car;
    int i = 0;
    while (car->next != NULL)
    {
        if (car->next->RS = 'S')
        {
            cat[i] = *(car->next);
            i++;
        }
        car = car->next;
    }
    for (int j = i; j < 10; j++)
        cat[i].num = -1;
    sort();
    car = gosh;
}

void jobsrs(char **str)
{
    if (str[1] == NULL)
    {
        jobsdispr();
        jobsdisps();
    }
    else if (strcmp("-r", str[1]) == 0)
    {
        jobsdispr();
    }
    else if (strcmp("-s", str[1]) == 0)
    {
        jobsdisps();
    }
    else
    {
        jobsdispr();
        jobsdisps();
    }
}
