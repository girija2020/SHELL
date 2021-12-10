#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char *homedir;
char olddir[1000];

void chd(char *string)
{
    int l = 0;
    if (strcmp(string, "-") != 0 & strcmp(string, "~") != 0)
    {
        olddir[1000] = '\0';
        getcwd(olddir, 1000);
        l = chdir(string);
    }
    if (l < 0)
    {
        perror("Sorry, the statue can't be found on the Marauder's Map ");
    }
    if (strcmp(string, "-") == 0)
    {
        char somedir[1000]="\0";
        getcwd(somedir, 1000);
        int x = chdir(olddir);
        if(x>0)
        {
            printf("Error");
        }
        //printf("%s\n",olddir);
        strcpy(olddir,somedir);
    }
    if (strcmp(string, "~") == 0)
    {
        olddir[1000] = '\0';
        getcwd(olddir, 1000);
        chdir(homedir);
    }
    return;
}