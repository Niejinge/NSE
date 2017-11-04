#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "linktable.h"

int quit();
int add(int argc,char *argv[]);
int sub(int argc,char *argv[]);

int main(int argc, char** argv);

int quit()
{
    exit(0);

    return 0;
}


int add(int argc, char* argv[])
{
    int i,r;
    if(argc !=3)
    {
        printf("warning input 2 numbers\n");
        return 0;
    }
    r=atoi(argv[1])+atoi(argv[2]);
    printf("result is %d\n",r);
    return 0;
}

int sub(int argc, char* argv[])
{
    int i,r;
    if(argc !=3)
    {
        printf("warning input 2 numbers\n");
        return 0;
    }
    r=atoi(argv[1])-atoi(argv[2]);
    printf("result is %d\n",r);
    return 0;
}

int main(int argc, char **argv) {
    MenuConfig("quit","quit from the menu program", quit);
    MenuConfig("add","here is a add demo", add);
    MenuConfig("sub","this is a sub demo", sub);

    ExecuteMenu();

    return 0;
}
