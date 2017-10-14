#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"
tLinkTable *CreateLinkTable()
{
    tLinkTable *pLinkTable=(tLinkTable*)malloc(sizeof(tLinkTable));
    pLinkTable->pHead=NULL;
    pLinkTable->SumOfNode=0;
    return pLinkTable;
}
int DeleteLInkTable(tLinkTable *pLinkTable)
{
    if(pLinkTable ==NULL)
    {
         return FAILURE;
    }
    if(pLinkTable->pHead ==NULL)
    {
        free(pLinkTable);
        return SUCCESS;
    }
    tLinkTableNode *pNode=GetLinkTableHead(pLinkTable);
    tLinkTableNode *pre;
    while(pNode !=NULL)
    {
        pre=pNode;
        pNode=GetNextLinkTableNode(pLinkTable,pNode);
        free(pre);
    }
    free(pNode);
    return SUCCESS;
 }
int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode *pNode)
{
    if(pLinkTable==NULL || pNode==NULL)
    {
        return FAILURE;
    }
    if(pLinkTable->pHead==NULL)
    {
        pLinkTable->pHead=pNode;
        pLinkTable->pTail=pNode;
        return SUCCESS;
    }
    tLinkTableNode *ptrNode=GetLinkTableHead(pLinkTable);
    while(ptrNode->pNext !=NULL)
    {
        ptrNode=ptrNode->pNext;
    }
    ptrNode->pNext=pNode;
    return SUCCESS;
}
int DelLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode *pNode)
{
    if(pLinkTable==NULL || pNode==NULL)
    {
        return FAILURE;
    }
    if(pLinkTable->pHead==NULL)
    {
        free(pLinkTable->pHead);
        return SUCCESS;
    }
    tLinkTableNode *pre=GetLinkTableHead(pLinkTable);
    while(pre->pNext !=pNode)
    {
        pre=pre->pNext;
    }
    tLinkTableNode *pTemp=pre->pNext;
    pre->pNext=pTemp->pNext;
    free(pTemp);
    return SUCCESS;
}
tLinkTableNode *GetLinkTableHead(tLinkTable *pLinkTable)
{
    if(pLinkTable ==NULL || pLinkTable->pHead==NULL)
    {
         return NULL;
    }
    tLinkTableNode *pNode=pLinkTable->pHead;
    return pNode;
}
tLinkTableNode *GetNextLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode *pNode)
{
    if(pLinkTable==NULL || pLinkTable->pHead==NULL)
    {
        return NULL;
    }
    tLinkTableNode *pre = pLinkTable->pHead;
    while(pre != NULL)
    {
        if(pre == pNode)
	    return pre->pNext;
        pre = pre->pNext;
    }
    return NULL;
}
