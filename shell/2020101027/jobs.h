#ifndef jobs
#define jobs

struct job{
    char RS;
    char name[100];
    int pid;
    int num;
    struct job* next;
};

void jobsdispr();
void jobsdisps();
void jobsrs(char** str);

#endif