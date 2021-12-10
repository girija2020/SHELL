#include <stdio.h>
#include "prompt.h"
#include <unistd.h>
#include "cd.h"
#include "ls.h"
#include "pinf.h"
#include "jobs.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>
extern struct job *jo;
extern struct job* car;

char *homedir;

void sig()
{
    signal(SIGTSTP, sig);
}

int main()
{
    char *string;
    char *dir = NULL;
    int x;
    char buf[1000] = "";
    getcwd(buf, 1000);
    homedir = buf;
    jo = malloc(sizeof(struct job));
    jo->next = NULL;
    jo->num = 0;
    jo = (struct job*)mmap(NULL, sizeof *jo, PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    car = jo;
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, sig);
    while (1)
    {
        fflush(stdin);
        char buf[1000] = "";
        getcwd(buf, 1000);
        dir = buf;
        getprompt(dir, homedir);
        x = readprompt();
    }
}