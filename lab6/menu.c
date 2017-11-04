#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linktable.h"
#include "menu.h"

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10


/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char*   cmd;
    char*   desc;
    int     (*handler)(int argc, char* argv[]);
} tDataNode;

tLinkTable * head = NULL;

int SearchCondition(tLinkTableNode * pLinkTableNode, void* args)
{
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    char* cmd = (char*)args;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;
    }
    return FAILURE;
}


tDataNode* FindCmd(tLinkTable * head, char * cmd)
{
    return  (tDataNode*)SearchLinkTableNode(head,SearchCondition,(void*)cmd);
}


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

int help()
{
    printf("=========================================\n");
    printf("List all the cmd of menu program:\n");
    ShowAllCmd(head);
    printf("=========================================\n");
}

int MenuConfig(char* cmd, char* desc, int (*handler)(int argc, char* argv[]))
{
    if(head == NULL)
    {
        head = CreateLinkTable();
        tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "List all the cmd of menu";
        pNode->handler = help;
        AddLinkTableNode(head, (tLinkTableNode *)pNode);
    }
    tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = cmd;
    pNode->desc = desc;
    pNode->handler = handler;
    AddLinkTableNode(head, (tLinkTableNode *)pNode);

    return 0;
}

int ExecuteMenu()
{

    char input[CMD_MAX_LEN];
    printf("If you need help, please type help\n");
    while(1)
    {
	int argc = 0;
	char* argv[CMD_MAX_LEN];
	char* cmd = NULL;

    	printf("cmd>>");
    	cmd = fgets(input, CMD_MAX_LEN, stdin);

	if(cmd == NULL)
	{
	    continue;
	}

	/*converts cmd to agrc and agrv*/
	cmd = strtok(cmd, " ");
	while(cmd != NULL && argc < CMD_MAX_LEN)
	{
	    argv[argc] = cmd;
	    argc ++;
            cmd = strtok(NULL, " ");
	}
	if(argc ==  1)
	{
	    int len = strlen(argv[0]);
	    *(argv[0] + (len - 1)) = '\0';
	}
    	tDataNode* p = FindCmd(head, argv[0]);
        if(p == NULL)
        {
            printf("the cmd you input isn't exist\n");
            continue;
        }
        if(p->handler != NULL)
        {
            p->handler(argc, argv);
        }

    }
    return 0;
}
