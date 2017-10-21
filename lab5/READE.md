
----------
**实验要求**

1. 给lab5-1.tar.gz找bug，quit命令无法运行的bug
2. 利用callback函数参数使Linktable的查询接口更加通用
3. 注意接口的信息隐藏

　 本次实验主要是从老师给的源代码里修改bug, 并优化代码,使用`caLlback`来完成,最后实现接口的隐藏,总体还是比较简单的,因为不用自己去写代码,只需要好好理解老师的讲解,并修改好即可。
<!--more-->

----------
* 修改bug

 　首先下载老师的代码并运行，发现quit命令不能识别，如下图所示：
![](https://i.imgur.com/3mPDbpK.jpg)

　 经过分析，发现在`inktable.c`中`SearchLinkTableNode`函数中有错误，while循环中最后一次循环到`pLinkTable->ptail`就终止了，因此quit作为最后一条命令不能识别。修改为NULL，就可以了，修改后代码如下：

	tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void* args), void* args)
	{
	    if(pLinkTable == NULL || Conditon == NULL)
	    {
	        return NULL;
	    }
	    tLinkTableNode * pNode = pLinkTable->pHead;
	    while(pNode != NULL)
	    {    
	        if(Conditon(pNode, args) == SUCCESS)
	        {
	            return pNode;				    
	        }
	        pNode = pNode->pNext;
	    }
	    return NULL;
	}
再运行程序，错误消失：
![](https://i.imgur.com/5KWhnjU.jpg)

* 使用`callback`优化代码

　 对于	callback,就是被调用函数还要利用调用者提供信息，来完成函数的实现。现在我们就来对我们的代码完成优化，通过引入callback来对代码进行修改，以降低代码的耦合程度。
　 之前的代码中，在menu.c中，`char cmd[CMD_MAX_LEN];`作为全局变量出现在main函数体外，这虽然实现了我们的目的，但是使用全局变量是不好的，这会无形之间增加代码之间的耦合程度。所以，我们要通过引入callback来降低耦合，使我们的代码更加完美。
为了实现我们的目的，通过在`SearchCondition`中引入args参数，可以实现把cmd的声明放在main函数体内，具体代码如下：

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
这里修改之后，相关地方都需要修改，总共需要修改的地方还有：

	tDataNode* FindCmd(tLinkTable * head, char * cmd)
	{
	    return  (tDataNode*)SearchLinkTableNode(head,SearchCondition, cmd);
	}

linktable.h和linktable.c中相关代码也需要修改：具体修改就不一一赘述了。

linktable.h:

	tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void* args), void* args);


linktable.c:

	tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void* args), void* args)
	{
	    if(pLinkTable == NULL || Conditon == NULL)
	    {
	        return NULL;
	    }
	    tLinkTableNode * pNode = pLinkTable->pHead;
	    while(pNode != NULL)
	    {    
	        if(Conditon(pNode, args) == SUCCESS)
	        {
	            return pNode;				    
	        }
	        pNode = pNode->pNext;
	    }
	    return NULL;
	}

* 实现代码的隐藏
　 通过把头文件中数据结构的定义移到.c文件中，而在头文件仅实现结构的定义，就实现了代码的隐藏，只提供接口，提高了代码的健壮性。

> **通过上面的优化，我们的代码基本要求已经实现了，试运行也没有出错，很高兴，接下来添加自己的几个小函数，然后运行一下，本次实验就宣告完毕了！**

因为本次实验是老师提供的源代码，这里就不全贴出来了，具体代码详情可见github。这里就贴出`menu.c`的代码吧，因为这是改动最大的源文件。
``` c
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
```

----------

* 实验结果

通过`gcc linktable.c menu.c -o menu`生成可执行文件，然后通过命令`./menu`运行文件，结果如下：
![](https://i.imgur.com/AJw91EW.jpg)

* 提交代码到github
![](https://i.imgur.com/Bgl8NMu.jpg)

----------
* 实验总结
 　 通过本次实验，深入理解了callback的机制，软件工程不只是能写出能执行的代码，更关键的是代码调优，通过callback和实现接口信息的隐藏，可以使我们的代码更加通用，更加健壮。这是思想是需要慢慢培养的，要在平时练习中注意使用，提高调优能力。


