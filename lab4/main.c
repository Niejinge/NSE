#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "linktable.h"

#define CMD_MAX_LEN 128
#define CMD_NUM 10
#define DESC_LEN 1024

int mathDemo();
int dogBark();
int showData();
int eat();
int add();
int sub();
int happy();
int quit();

typedef struct DataNode
{
    tLinkTableNode *pNext;
    char*  cmd;
    char*  desc;
    int    (*handler)();
} tDataNode;

void InitMenu(tLinkTable ** pLinkTable);
tDataNode* FindCmd(tLinkTable *head, char *cmd);
int ShowAllCmd(tLinkTable *head);
tLinkTable * head = NULL;
int main()
{
    InitMenu(&head);
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
	printf("%s - %s:\n", p->cmd, p->desc);
	if(p->handler != NULL)
	{
	    p->handler();
	    printf("====================================\n");
	}
    }  
    return 0;
}
void InitMenu(tLinkTable ** pLinkTable)
{
    *pLinkTable = CreateLinkTable();
    tDataNode * pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "mathDemo";
    pNode->desc = "This is a simple math demo.";
    pNode->handler = mathDemo;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "dogBark";
    pNode->desc = "a dog bark at the midnight!";
    pNode->handler = dogBark;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);
 
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "showData";
    pNode->desc = "all the cmd list here:";
    pNode->handler = showData;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "eat";
    pNode->desc = "it's supper time, let's eat some food";
    pNode->handler = eat;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "add";
    pNode->desc = "add two demo of numbers.";
    pNode->handler = add;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "sub";
    pNode->desc = "sub two demo of two numbers.";
    pNode->handler = sub;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);
 
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "happy";
    pNode->desc = "keep smile in life everyday!";
    pNode->handler = happy;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);

    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "exit the program";
    pNode->handler = quit;
    AddLinkTableNode(*pLinkTable, (tLinkTableNode *)pNode);
   
}
tDataNode* FindCmd(tLinkTable *head, char *cmd)
{
    tDataNode *pNode = (tDataNode*)GetLinkTableHead(head);
    while (pNode != NULL)
    {
        if (strcmp(pNode->cmd, cmd) == 0)
        {
            return pNode;
        }
        pNode = (tDataNode*)GetNextLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    return NULL;
}

int ShowAllCmd(tLinkTable *head)
{
    tDataNode *pNode = (tDataNode*)GetLinkTableHead(head);
    while (pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        printf("====================================\n");
        pNode = (tDataNode*)GetNextLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    return 0;
}

int mathDemo()
{
    printf("1 + 2 = %d\n", 1+2);
    return 0;
}

int dogBark()
{
    printf("Ruff! Ruff! Ruff ... !\n");
    return 0;
}

int showData()
{
    ShowAllCmd(head);
    return 0;
}

int eat()
{
    printf("uh..! The meat is declicious!\n");
    return 0;
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

int happy()
{
    printf("hahaheheheiheixixihouhouxiaxia!\n");
    return 0;
}

int quit()
{
    exit(0);
    return 0;
}
