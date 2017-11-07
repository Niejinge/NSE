# 高软实验报告7

> 网易云课堂昵称: 镍铬合金  
学号:sa17225259  
github: [https://github.com/Niejinge/NSE](https://github.com/Niejinge/NSE "https://github.com/Niejinge/NSE")  
《软件工程（C编码实践篇）》MOOC课程作业http://mooc.study.163.com/course/USTC-1000002006 】


----------
**实验要求**

1. 为menu子系统设计接口，并写用户范例代码来实现原来的功能；
2. 使用make和make clean来编译程序和清理自动生成的文件；
3. 使menu子系统支持带参数的复杂命令，并在用户范例代码中自定义一个带参数的复杂命令；
4. 可以使用getopt函数获取命令行参数。
<!--more-->
* **实验思路: 本次实验难度不高,在理解原理的情况下,实现试验要求,主要是学习了新知识,通过新建一个Makefile文件,可以一键实现很多功能,这对我们的代码简洁性,以及在编译链接阶段很有好处.**

## 实验流程
* 编写`menu.h`
``` c
int MenuConfig(char *cmd, char *desc, int (*handler)(int argc, char *argv[]));
	    	
int ExecuteMenu();
```
* 编写`menu.c`

```c
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
```

* 编写`Makefile`

``` c
CC_PTHREAD_FLAGS	= -lpthread
CC_FLAGS		= -c
CC_OUTPUT_FLAGS		= -o
CC			= -gcc
RM			= rm
RM_FLAGS		= -f

TARGET = test
OBJS = linktable.o menu.o test.o

all:	$(OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) $<

clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGET) *.bak
```

* 编写`test.c`

``` c
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
```

> linktable.h 和linktable.c与上次实验一样,所以就不贴上来了,具体可见github

* 试验结果

运行截图如下:
![](https://i.imgur.com/Sji7jtt.jpg)

* 提交到github代码库
![](https://i.imgur.com/OB8YGwd.jpg)

----------
* 试验总结

学习了一些新东西,相信对以后会很有帮助,比如makefile, strtok, getopt等等. 但是实验中还是出现了很多问题,比如之前提交到代码库一直没有问题,这次突然就提交不了了,具体是关于分支master之前提交过,又改变了本地库之后再次提交出问题,百度也没找出答案,心里很烦躁,好在最后解决了问题,美中不足的是没有去研究为什么会出问题,瞎解决就完事了,希望下次不要再遇到,不然还是过不了这个坎.
