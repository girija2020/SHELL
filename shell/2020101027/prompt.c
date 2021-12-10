#include "prompt.h"
#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "parse.h"
#include <stdlib.h>
#include <sys/types.h>

void getprompt(char *dir, char *homedir)
{
    struct utsname try;
    int value = uname(&try);

    if (value < 0)
    {
        perror("Error in prompting the system name: ");
        return;
    }

    int len = strlen(homedir);
    int l = 1;

    for (int i = 0; i < len; i++)
    {
        if (dir[i] != homedir[i])
        {
            l = 0;
            break;
        }
    }
    int q = strlen(dir);
    if (l == 1)
    {
        if (q - len != 0)
        {
            for (int i = 0; i < q - len; i++)
            {
                dir[i] = dir[i + len];
            }
            for (int i = q - len; i < q; i++)
            {
                dir[i] = '\0';
            }
        }
        else
            dir = NULL;
    }

    uid_t uid = geteuid();
    struct passwd *bry = getpwuid(uid);

    char name[1000] = "";
    strcpy(name, bry->pw_name);

    strcat(name, "@");
    strcat(name, try.sysname);
    strcat(name, ":");

    if (l == 1)
    {
        strcat(name, "~");
        if (q - len != 0)
        {
            strcat(name, dir);
            printf("<%s>", name);
        }
        else
        {
            printf("<%s>", name);
        }
    }
    else
    {
        strcat(name, dir);
        printf("<%s>", name);
    }
}

int readprompt()
{
    fflush(stdin);
    fflush(stdout);
    char buf[150];
    for (int i = 0; i < 150; i++)
    {
        buf[i] = '\0';
    }
    int l = 0;
    do
    {
        buf[l] = getchar();
        if(buf[l] < 0)
        {
            exit(0);
        }
        l++;
    } while (buf[l - 1] != '\n');
    char *string[125];
    for (int i = 0; i < 125; i++)
    {
        string[i] = NULL;
    }
    int i = 0;
    string[0] = strtok(buf, ";");
    if (strcmp(string[0], "\n") != 0)
    {
        while (string[i] != NULL)
        {
            i++;
            string[i] = strtok(NULL, ";");
        }
    }
    i = 0;
    while (string[i] != NULL)
    {
        par(string[i]);
        i++;
    }
    return 0;
}