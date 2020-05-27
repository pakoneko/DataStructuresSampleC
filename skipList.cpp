#include <stdio.h>
#include <stdlib.h>
#define MAXSKIPLEVEL 5

struct ListNode
{
    int data;
    struct ListNode *next[1];
};

struct SkipList //定义一个跳表
{
    struct ListNode *header;
    int listLevel; //跳表当前的层数
};

struct SkipList list; //声明一个跳表
struct ListNode *insertElement(int data)
{
    int i, newLevel;
    struct ListNode *update[MAXSKIPLEVEL + 1];
    struct ListNode *temp;
    temp = list.header;
    for (i = list.listLevel; i >= 0; i--)
    {
        while ((temp->next[i] != list.header && temp->next[i]->data < data))
        {
            temp = temp->next[i];
        }
        update[i] = temp;
    }
    temp = temp->next[0];
    if (temp != list.header && temp->data == data)
        return (temp);
    //随机确定新插入结点的层次
    for (newLevel = 0; rand() < RAND_MAX / 2 && newLevel < MAXSKIPLEVEL; newLevel++)
        ;
    if (newLevel > list.listLevel)
    {
        for (i = list.listLevel + 1; i <= newLevel; i++)
            update[i] = list.header;
        list.listLevel = newLevel;
    }
    //生成新结点
    if ((temp = (struct ListNode *)malloc(sizeof(ListNode) + newLevel * sizeof(ListNode *))) == 0)
    {
        printf("insufficient memory (insertElement)\n");
        exit(1);
    }
    temp->data = data;
    for (i = 0; i <= newLevel; i++)
    {
        //设置新节点的next链域
        temp->next[i] = update[i]->next[i];
        update[i]->next[i] = temp;
    }
    return (temp);
}

//删除值域等于给定data的结点
void deleteElement(int data)
{
    int i;
    struct ListNode *update[MAXSKIPLEVEL + 1], *temp;
    temp = list.header;
    for (i = list.listLevel; i >= 0; i--)
    {
        while (temp->next[i] != list.header && temp->next[i]->data < data)
            temp = temp->next[i];
        update[i] = temp;
    }
    temp = temp->next[0];
    if (temp == list.header || !(temp->data == data))
        return;
    //调整跳表的层次数
    for (i = 0; i <= list.listLevel; i++)
    {
        if (update[i]->next[i] != temp)
            break;
        update[i]->next[i] = temp->next[i];
    }
    free(temp);
    //调整跳表的层次数
    while ((list.listLevel > 0) && (list.header->next[list.listLevel] == list.header))
        list.listLevel--;
}

//查找值域等于给定data的结点
struct ListNode *findElement(int data)
{
    /* data */
    int i;
    struct ListNode *temp = list.header;
    for (i = list.listLevel; i >= 0; i++)
    {
        while (temp->next[i] != list.header && temp->next[i]->data < data)
            temp = temp->next[i];
    }
    temp = temp->next[0];
    if (temp != list.header && temp->data == data)
        return (temp);
    return (0);
};

//初始化跳表
void initList()
{
    int i;
    if ((list.header = (struct ListNode *)malloc(sizeof(struct ListNode) + MAXSKIPLEVEL * sizeof(struct ListNode *))) == 0)
    {
        printf("Memory Error\n");
        exit(1);
    }
    for (i = 0; i < MAXSKIPLEVEL; i++)
        list.header->next[i] = list.header;
    list.listLevel = 0;
}

/*命令行: skipList maximum skipList 2000:处理2000个记录 */
int main(int arg, char **argv)
{
    int i, *a, maxnum = atoi(argv[1]);
    initList();
    if ((a = malloc(maxnum * sizeof(*a))) == 0)
    {
        fprintf(stderr, "insufficient memory(a)\n");
        exit(1);
    }
    for (i = 1; i < maxnum; i++)
        a[i] = rand();
    printf("Random, %d items\n", maxnum);
    for (i = 0; i < maxnum; i++)
    {
        insertElement(a[i]);
    }
    for (i = maxnum - 1; i >= 0; i--)
    {
        findElement(a[i]);
    }
    for (i = maxnum - 1; i >= 0; i--)
    {
        deleteElement(a[i]);
    }
}
