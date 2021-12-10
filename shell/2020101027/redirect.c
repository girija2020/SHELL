#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
extern int pid7;

void red(char **str)
{
    int i = 0;
    char *strin = NULL;
    char *strout = NULL;
    char *strapp = NULL;
    char *buf = NULL;
    int pid;
    int fd;
    while (str[i] != NULL)
    {
        if (strcmp(str[i], "<") == 0)
        {
            if (str[i + 1] != NULL)
                strin = str[i + 1];
            else
            {
                printf("Supply an input");
                return;
            }
            if (str[i + 1] != NULL)
            {
                fd = open(strin, O_RDONLY);
                read(fd, buf, 10000);
                close(fd);
                int f = i + 1;
                int w = i;
                while (str[w] != NULL)
                {
                    str[w] = str[f];
                    w++;
                    f++;
                }
                str[w] = NULL;
            }
        }
        else if (strcmp(str[i], ">") == 0)
        {
            strout = str[i + 1];
            pid = fork();
            if (pid == 0)
            {
                if (strout == NULL)
                {
                    exit(0);
                }
                pid7 = pid;
                remove(strout);
                fd = open(strout, O_CREAT | O_RDWR, 0644);
                dup2(fd, STDOUT_FILENO);
                str[i] = NULL;
                str[i++] = NULL;
                return;
            }
            else
            {
                wait(0);
                int f = i + 2;
                int w = 0;
                while (str[f] != NULL)
                {
                    str[w] = str[f];
                    w++;
                    f++;
                }
                str[w] = NULL;
                return;
            }
        }
        else if (strcmp(str[i], ">>") == 0)
        {
            strapp = str[i + 1];
            pid = fork();
            if (pid == 0)
            {
                pid7 = pid;
                fd = open(strapp, O_APPEND | O_WRONLY);
                int x = dup2(fd, STDOUT_FILENO);
                perror("");
                str[i] = NULL;
                str[i++] = NULL;
                return;
            }
            else
            {
                wait(0);
                int f = i + 2;
                int w = 0;
                while (str[f] != NULL)
                {
                    str[w] = str[f];
                    w++;
                    f++;
                }
                str[w] = NULL;
                return;
            }
        }
        i++;
    }
    return;
}
