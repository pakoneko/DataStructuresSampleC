#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int blockSize; //块中包含的最大结点个数

//定义节点
struct ListNode
{
    struct ListNode *next;
    int value;
};

//定义块
struct LinkedBlock
{
    struct LinkedBlock *next;
    struct ListNode *head;
    int nodeCount;
};

struct LinkedBlock *blockHead; //定义块的头标记

//创建一个空块
struct LinkedBlock *newLinkedBlock()
{
    struct LinkedBlock *block = (struct LinkedBlock *)malloc(sizeof(struct LinkedBlock)); //分配块的内存
    block->next = NULL;
    block->head = NULL;
    block->nodeCount = 0;
    return block;
}

//创建一个结点
struct ListNode *newListNode(int value)
{
    struct ListNode *temp = (struct ListNode *)malloc(sizeof(struct ListNode));
    temp->next = NULL;
    temp->value = value;
    return temp;
}

void searchElement(int k, struct LinkedBlock **fLinkedBlock, struct ListNode **fListNode)
{
    //找到第k个结点和它所在的块
    int j = (k + blockSize - 1) / blockSize; //第k个结点在第j块中
    struct LinkedBlock *p = blockHead;       //设置p为块的头标记
    while (--j)
    {
        p = p->next;
    }
    *fLinkedBlock = p;
    //在p所指的块种找到目标结点
    struct ListNode *q = p->head;
    k = k % blockSize;
    if (k == 0)
        k = blockSize;
    k = p->nodeCount + 1 - k;
    while (k--)
    {
        q = q->next;
    }
    *fListNode = q;
}

//从*p块开始移动操作
void shift(struct LinkedBlock *A)
{
    struct LinkedBlock *B;
    struct ListNode *temp;
    //如果块的节点数大于规定大小，那么继续移动
    while (A->nodeCount > blockSize)
    {
        if (A->next == NULL) //A块后续没有块则新建一个块再移入
        {
            //到达松散链表的表尾，这个情况下的处理稍有不同
            A->next = newLinkedBlock();
            B = A->next;
            temp = A->head->next;                //临时的指针变量指向A的尾部
            A->head->next = A->head->next->next; //A的首结点next指针挪到倒数第二个结点，temp指的结点从A中删除
            B->head = temp;                      //块B的首元结点指针域指向temp所指结点
            temp->next = temp;                   //temp的next指针指向自己 (因为这时候块B只有temp一个元素)
            A->nodeCount--;
            B->nodeCount++;
        }
        else
        {
            B = A->next;                         //设置B为A块后续
            temp = A->head->next;                //临时的指针变量指向A的尾部
            A->head->next = A->head->next->next; //A的第一个结点next指针挪到倒数第二个结点，temp指的结点从A中删除
            temp->next = B->head->next;          //temp的next结点 指向 B的头指针结点next
            B->head->next = temp;                //块B的首元结点的next指针域 指向temp所指结点
            B->head = temp;                      //修改块B的头指针指向temp所指的结点。丢弃temp指针
            A->nodeCount--;                      //A减少元素统计
            B->nodeCount++;                      //B增加元素统计
        }
        A = B; //继续下一个块的循环
    }
}

void addElement(int k, int x)
{
    struct ListNode *p, *q;
    struct LinkedBlock *r;
    if (!blockHead)
    { //如果首个块不存在，新创建一个块
        blockHead = newLinkedBlock();
        blockHead->head = newListNode(x);        //首元结点新建一个结点，值为x
        blockHead->head->next = blockHead->head; //next指向首元结点 因为这个块只有一个结点
        blockHead->nodeCount++;
    }
    else
    {
        if (k == 0)
        {
            //松散链表不为空时，在第k=0个位置上插入
            p = blockHead->head;      //p为第一个块的首元
            q = p->next;              //q为首元后续的结点
            p->next = newListNode(x); //
            p->next->next = q;
            blockHead->head = p->next;
            blockHead->nodeCount++;
            shift(blockHead); //相应的移动块中的结点 达到结点个数平衡
        }
        else
        {
            //在其他位置上插入
            //该子程序返回时，r指向第k个结点所在的块，p指向第k个结点
            searchElement(k, &r, &p);
            q = p;
            while (q->next != p)
                q = q->next;
            q->next = newListNode(x); //新建一个结点
            q->next->next = p;
            r->nodeCount++;
            shift(r);
        }
    }
}

int searchElement(int k) //查找链表第k个结点
{
    struct ListNode *p;       // 设置结点p
    struct LinkedBlock *q;    // 设置链表块 q
    searchElement(k, &q, &p); //查找第k个结点和它所在的块
    return p->value;          //获取并返回结点的值
}

int testUnRolledLinkedList()
{
    int tt = clock();
    int m, i, k, x;
    char cmd[10];
    scanf("%d", &m);
    blockSize = (int)(sqrt(m - 0.001)) + 1;
    for (i = 0; i < m; i++)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "add") == 0)
        {
            scanf("%d %d", &k, &x);
            addElement(k, x);
        }
        else if (strcmp(cmd, "search") == 0)
        {
            scanf("%d", &k);
            printf("%d\n", searchElement(k));
        }
        else
        {
            fprintf(stderr, "Wrong Input\n");
        }
    }
    return 0;
}

int main()
{
    return testUnRolledLinkedList();
}
