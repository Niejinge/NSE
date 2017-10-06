#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

void mathDemo();
void dogBark();
int showData();
void eat();
int add();
int sub();
void happy();
void quit();

#define CMD_MAX_LEN 128
#define CMD_NUM 10
#define DESC_LEN 1024

static tDataNode head[] =
{
    {"mathDemo", "this is a simple math demo.", mathDemo, &head[1]},
    {"dogBark", "a dog bark at the night!", dogBark, &head[2]},
    {"showData", "this is the data list.", showData, &head[3]},
    {"eat", "it's supper time, let's eat some food", eat, &head[4]},
    {"add", "add demo of two numbers.", add, &head[5]},
    {"sub", "sub demo of two numbers.", sub, &head[6]},
    {"happy", "keep smile in life!", happy, &head[7]},
    {"quit", "exit the program", quit, NULL}
};

int main()
{
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("please input a command->");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        if(p==NULL)
        {
	    printf("this is a wrong cmd!\n");
	    continue;
        }
	printf("%s - %s", p->cmd, p->desc);
	if(p->handler != NULL)
	{
	    p->handler();
	}
    }   
}

void mathDemo()
{
    printf("1 + 2 = %d\n", 1+2);
}

void dogBark()
{
    printf("Ruff! Ruff! Ruff ... !\n");
}

int showData()
{
    ShowAllCmd(head);
}

void eat()
{
    printf("uh..! The meat is declicious!\n");
}

int add()
{
    int x, y;
    printf("input two numbers:\n");
    scanf("%d %d", &x, &y);
    printf("x+y = %d\n", x+y);
    return 0;
}

int sub()
{
    int x, y;
    printf("input two numbers:\n");
    scanf("%d %d", &x, &y);
    printf("x-y = %d\n", x-y);
    return 0;
}

void happy()
{
    printf("hahaheheheiheixixihouhouxiaxia!\n");
}

void quit()
{
    exit(0);
}
