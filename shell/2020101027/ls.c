#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <stdlib.h>
extern char *homedir;
extern int pid7;
extern int fd;

char *getpath(char *d_name, char *dir)
{
    if (strcmp(dir, "/") != 0)
        strcat(dir, "/");
    strcat(dir, d_name);
    return dir;
}

int getauthor(char *somedir)
{
    struct stat auth;
    stat(somedir, &auth);
    uid_t userid = auth.st_uid;
    struct passwd *pwd;
    pwd = getpwuid(userid);
    long int blk = auth.st_nlink;
    struct group *grp;
    grp = getgrgid(pwd->pw_gid);
    printf(" %3ld", blk);
    printf(" %s %s", pwd->pw_name, grp->gr_name);
    long long int size = auth.st_size;
    printf("%15lld", size);
    struct timespec times = auth.st_ctim;
    char buff[100] = "";
    strftime(buff, sizeof buff, "%h", localtime(&times.tv_sec));
    printf(" %s", buff);
    char buffer[100] = "";
    strftime(buffer, sizeof buffer, "%y", localtime(&times.tv_sec));
    //printf(" %s", buffer);
    time_t timenow;
    //struct tm* info;
    time(&timenow);
    char buffere[100] = "";
    strftime(buffere, sizeof buffere, "%y", localtime(&timenow));
    //printf(" %s", buffere);
    int l = 1;
    for (int i = 0; i < 100; i++)
    {
        if (buffer[i] != buffere[i])
        {
            l = 0;
            break;
        }
    }
    if (l == 1)
    {
        char buffe[100] = "";
        strftime(buffe, sizeof buffe, "%d %H:%M", localtime(&times.tv_sec));
        printf(" %s", buffe);
    }
    else
    {
        char buffe[100] = "";
        strftime(buffe, sizeof buffe, "    20%y", localtime(&times.tv_sec));
        printf(" %s", buffe);
    }
    return auth.st_blocks;
}

void getpermissions(char *somedir)
{
    struct stat perm;
    stat(somedir, &perm);
    int l = S_ISDIR(perm.st_mode);
    int q = S_ISREG(perm.st_mode);
    if (l == 1)
    {
        printf("d");
    }
    else
    {
        printf("-");
    }

    int q1, q2, q3, r1, r2, r3, s1, s2, s3;
    q1 = (perm.st_mode & S_IRUSR); //to check if it is user readable. if yes it returns octal(400)
    if (q1 == 256 & (q == 1 | l == 1))
    {
        printf("r");
    }
    else
    {
        printf("-");
    }

    q2 = (perm.st_mode & S_IWUSR); //to check if it is user writable. if yes it returns octal(200)
    if (q2 == 128 & (q == 1 | l == 1))
    {
        printf("w");
    }
    else
    {
        printf("-");
    }

    q3 = (perm.st_mode & S_IXUSR); //to check if it is user executable. if yes it returns octal(100)
    if (q3 == 64 & (q == 1 | l == 1))
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    r1 = (perm.st_mode & S_IRGRP); //to check if it is grp readable. if yes it returns octal(040)
    if (r1 == 32 & (q == 1 | l == 1))
    {
        printf("r");
    }
    else
    {
        printf("-");
    }

    r2 = (perm.st_mode & S_IWGRP); //to check if it is grp writable. if yes it returns octal(020)
    if (r2 == 16 & (q == 1 | l == 1))
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    r3 = (perm.st_mode & S_IXGRP); //to check if it is grp executable. if yes it returns octal(010)
    if (r3 == 8 & (q == 1 | l == 1))
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    s1 = (perm.st_mode & S_IROTH); //to check if it is others readable. if yes it returns octal(004)
    if (s1 == 4 & (q == 1 | l == 1))
    {
        printf("r");
    }
    else
    {
        printf("-");
    }

    s2 = (perm.st_mode & S_IWOTH); //to check if it is others writable. if yes it returns octal(002)
    if (s2 == 2 & (q == 1 | l == 1))
    {
        printf("w");
    }
    else
    {
        printf("-");
    }

    s3 = (perm.st_mode & S_IXOTH); //to check if it is others executable. if yes it returns octal(001)
    if (s3 == 1 & (q == 1 | l == 1))
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
}

void something(int a, int l, char *dir)
{
    char somedir[50] = "\0";
    strcpy(somedir, dir);
    if (a == 1 & l == 0)
    {
        DIR *directory = opendir(dir);
        if (directory == NULL)
        {
            int file = open(dir, O_RDONLY);
            if (file < 0)
            {
                perror("OOPS this file can't be found on the map");
                return;
            }
            else
            {
                printf("%s\n", dir);
                close(file);
                return;
            }
        }

        struct dirent *direntry = readdir(directory);
        while (direntry != NULL)
        {
            printf("%s\n", direntry->d_name);
            direntry = readdir(directory);
        }
        closedir(directory);
    }

    if (a == 0 & l == 0)
    {
        DIR *directory = opendir(dir);
        if (directory == NULL)
        {
            int file = open(dir, O_RDONLY);
            if (file < 0)
            {
                perror("OOPS this file can't be found on the map");
                return;
            }
            else
            {
                printf("%s\n", dir);
                close(file);
                return;
            }
        }
        struct dirent *direntry = readdir(directory);
        while (direntry != NULL)
        {
            if (direntry->d_name[0] != '.')
            {
                printf("%s\n", direntry->d_name);
            }
            direntry = readdir(directory);
        }
        closedir(directory);
    }

    if (a == 0 & l == 1)
    {
        DIR *directory = opendir(dir);
        if (directory == NULL)
        {
            int file = open(dir, O_RDONLY);
            if (file < 0)
            {
                perror("OOPS this file can't be found on the map");
                return;
            }
            else
            {
                getpermissions(dir);
                getauthor(dir);
                printf(" %s\n", dir);
                close(file);
                return;
            }
        }
        struct dirent *direntry = readdir(directory);
        int blocks = 0;
        while (direntry != NULL)
        {
            if (direntry->d_name[0] != '.')
            {
                char someotherdir[1000];
                strcpy(someotherdir, somedir);
                char *somethin = getpath(direntry->d_name, someotherdir);
                getpermissions(somethin);
                int blk=getauthor(somethin);
                printf(" ");
                blocks = blocks + blk;
                printf("%s\n", direntry->d_name);
            }
            direntry = readdir(directory);
        }
        printf("Total: %d\n",blocks/2);
        closedir(directory);
    }

    if (a == 1 & l == 1)
    {
        DIR *directory = opendir(dir);
        if (directory == NULL)
        {
            int file = open(dir, O_RDONLY);
            if (file < 0)
            {
                perror("OOPS this file can't be found on the map");
                return;
            }
            else
            {
                getpermissions(dir);
                getauthor(dir);
                printf(" %s\n", dir);
                close(file);
                return;
            }
        }
        struct dirent *direntry = readdir(directory);
        int blocks = 0;
        while (direntry != NULL)
        {
            char someotherdir[1000];
            strcpy(someotherdir, somedir);
            char *somethin = getpath(direntry->d_name, someotherdir);
            getpermissions(somethin);
            int blk=getauthor(somethin);
            printf(" ");
            printf("%s\n", direntry->d_name);
            blocks = blocks + blk;
            direntry = readdir(directory);
        }
        printf("Total: %d\n",blocks/2);
        closedir(directory);
    }
    return;
}

void comls(char **string)
{
    char somedir[50] = "\0";
    getcwd(somedir, 50);
    int i = 1;
    int a = 0;
    int l = 0;
    char strt[15][100];
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<100;j++)
        {
            strt[i][j]='\0';
        }
    }
    int j = 0;
    while (string[i] != NULL)
    {
        char *dir = somedir;
        if (strcmp(string[i], "-a") == 0)
        {
            a = 1;
        }
        else if (strcmp(string[i], "-l") == 0)
        {
            l = 1;
        }
        else if (strcmp(string[i], "-al") == 0)
        {
            a = 1;
            l = 1;
        }
        else if (strcmp(string[i], "-la") == 0)
        {
            a = 1;
            l = 1;
        }
        else if (strcmp(string[i], "..") == 0)
        {
            char *str[10];
            for (int i = 0; i < 10; i++)
            {
                str[i] = NULL;
            }
            char somedirec[200] = "";
            str[0] = strtok(dir, "/");
            int p = 0;
            while (str[p] != NULL)
            {
                str[p + 1] = strtok(NULL, "/");
                p++;
            }
            int q = 0;
            strcat(somedirec, "/");
            while (q < p - 2)
            {
                strcat(somedirec, str[q]);
                strcat(somedirec, "/");
                q++;
            }
            if (q < p - 1)
                strcat(somedirec, str[q]);
            strcpy(dir, somedirec);
            strcpy(strt[j], somedirec);
            j++;
        }
        else if (strcmp(string[i], "~") == 0)
        {
            dir = NULL;
            dir = homedir;
            strcpy(strt[j], dir);
            j++;
        }
        else
        {
            dir = NULL;
            dir = string[i];
            strcpy(strt[j], dir);
            j++;
        }
        i++;
    }

    if (j == 0)
    {
        something(a, l, somedir);
    }
    else
    {
        for (int i = 0; i < j; i++)
        {
            printf("%s :\n",strt[i]);
            something(a, l, strt[i]);
        }
    }
}