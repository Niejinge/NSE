#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"
#include <string.h>
int Help();
int Quit();
int dogBark();
int eat();
int add();
int sub();
int happy();
#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM    

/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char*   cmd;
    char*   desc;
    int     (*handler)();
} tDataNode;

int SearchCondition(tLinkTableNode * pLinkTableNode, void* args)
{
    char * cmd = (char*) args;
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;	       
}

/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(tLinkTable * head, char * cmd)
{
    return  (tDataNode*)SearchLinkTableNode(head,SearchCondition, cmd);
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable * head)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode *)pNode);
    }
    return 0;
}

int InitMenuData(tLinkTable ** ppLinktable)
{
    *ppLinktable = CreateLinkTable();
    tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "Menu List:";
    pNode->handler = Help;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "version";
    pNode->desc = "Menu Program V1.0";
    pNode->handler = NULL; 
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "Quit from Menu Program V1.0";
    pNode->handler = Quit; 
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
 
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "dogBark";
    pNode->desc = "a dog bark at the midnight!";
    pNode->handler = dogBark;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "eat";
    pNode->desc = "it's supper time, let's eat some food";
    pNode->handler = eat;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "add";
    pNode->desc = "add two demo of numbers.";
    pNode->handler = add;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "sub";
    pNode->desc = "sub two demo of two numbers.";
    pNode->handler = sub;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "happy";
    pNode->desc = "keep smile in life everyday!";
    pNode->handler = happy;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);   
    
    return 0; 
}

/* menu program */

tLinkTable * head = NULL;

int main()
{
    char cmd[CMD_MAX_LEN];
    InitMenuData(&head); 
   /* cmd line begins */
    while(1)
    {
        printf("Input a cmd number > ");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        if( p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc); 
        if(p->handler != NULL) 
        { 
            p->handler();
        }
   
    }
}

int Help()
{
    ShowAllCmd(head);
    return 0; 
}

int Quit()
{
    exit(0);
}

int dogBark()
{
    printf("Ruff! Ruff! Ruff ... !\n");
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
