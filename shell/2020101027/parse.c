#include "parse.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include "cd.h"
#include "execvp.h"
#include "ls.h"
#include "pinf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include "jobs.h"
#include "sign.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fg.h>
#include <bg.h>
#include "execvp.h"
#include "redirect.h"
int pid7 = 1;
int fd = -1;
extern char *homedir;
int fds[2];
int hello = -1;
int fdd[2];
int x;

int get_index(char *str)
{

    char *strings[11] = {"cd", "pwd", "echo", "ls", "pinfo", "repeat", "exit", "jobs", "fg", "bg", "sig"};
    int n = 11;
    while (n != 0 & str != NULL)
    {
        n--;
        if (strcmp(str, strings[n]) == 0)
            return n + 1;
    }
    return 0;
}

void par(char *string)
{
    char *str[125];
    for (int i = 0; i < 125; i++)
    {
        str[i] = NULL;
    }
    int i = 0;
    int num = 0;
    str[0] = strtok(string, " \n\t");
    while (str[i] != NULL)
    {
        if (strcmp(str[i], "|") == 0)
        {
            num++;
        }
        i++;
        str[i] = strtok(NULL, " \n\t");
    }
    i = 0;
    int input;
    int output;
    input = 0;
    output = 1;
    while (str[i] != NULL)
    {
        if (strcmp(str[i], "|") == 0)
        {
            int num;

            pipe(fds);
            pid_t pid = fork();
            if (pid == 0)
            {
                pid7 = pid;
                str[i] = NULL;
                close(fds[0]);
                int x = dup2(fds[1], output);
                if (x < 0)
                    perror("");
                goto L0;
            }
            else
            {
                wait(0);
                pid_t pid2 = fork();
                pid7 = pid2;
                if (pid2 == 0)
                {
                    close(fds[1]);
                    int f = i + 1;
                    int w = 0;
                    str[w] = str[f];
                    int x = dup2(fds[0], input);
                    close(fds[0]);
                    if (x < 0)
                    {
                        perror("");
                    }
                    dup2(output, output);
                    output = dup(input);
                    w = 1;
                    f = i + 2;
                    int p = 0;
                    while (str[f] != NULL)
                    {
                        if (strcmp(str[f], "|") != 0)
                        {
                            if (strcmp(str[f], ">") != 0 | (strcmp(str[f], ">>") != 0))
                            {
                                str[w] = str[f];
                                w++;
                                f++;
                            }
                            else
                            {
                                pid7 = pid;
                                str[w] = "/proc/self/fd/0";
                                str[w + 1] = str[f];
                                str[w + 2] = str[f + 1];
                                str[w + 3] = NULL;
                                w = 0;
                                while(str[w] != NULL)
                                {
                                    printf("%s",str[w]);
                                    w++;
                                }
                                goto L0;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    pid7 = 0;
                    str[w] = "/proc/self/fd/0";
                    str[w + 1] = NULL;
                    w = 0;
                    goto L0;
                }
                else
                {
                    close(fds[0]);
                    close(fds[1]);
                    wait(0);
                    int w = 0;
                    int f = i + 2;
                    int p = 0;
                    while (str[f] != NULL)
                    {
                        if (strcmp(str[f], "|") != 0)
                        {
                            f++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    while (str[f + 1] != NULL)
                    {
                        str[w] = str[f + 1];
                        w++;
                        f++;
                    }
                    str[w] = NULL;
                    i = -1;
                }
            }
        }
        i++;
    }
L0:
    red(str);
    x = 1;
L1:
    for (int k = 0; k < x; k++)
    {
        int index = get_index(str[0]);
        i = 1;
        char pwd[50] = "\0";
        int q = 1;
        int p = 0;
        switch (index)
        {
        case 1:
            if (str[i] != NULL)
            {
                chd(str[i]);
                i++;
                if (str[i] != NULL)
                {
                    printf("Only one straw allowed at a time for this butterbeer\n");
                }
            }
            break;
        case 2:
            getcwd(pwd, 50);
            printf("%s\n", pwd);
            break;
        case 3:
            while (str[q] != NULL)
            {
                printf("%s ", str[q]);
                q++;
            }
            printf("\n");
            break;
        case 4:
            comls(str);
            break;
        case 5:
            pinfo(str);
            break;
        case 6:
            i = 0;
            if (str[i + 1] == NULL)
            {
                break;
            }
            x = atoi(str[i + 1]);
            if (x == 0)
            {
                printf("This spell has more to it, you need to give the number too\n");
                break;
            }
            while (str[i + 2] != NULL)
            {
                str[i] = str[i + 2];
                i++;
            }
            str[i] = NULL;
            str[i + 1] = NULL;
            goto L1;
            break;
        case 7:
            exit(0);
        case 8:
            jobsrs(str);
            break;
        case 9:
            fgc(str);
            break;
        case 10:
            bgc(str);
            break;
        case 11:
            sigc(str);
            break;
        default:
            exec(str);
            break;
        }
    }
    if (pid7 == 0)
    {
        close(fds[1]);
        exit(0);
    }
    return;
}