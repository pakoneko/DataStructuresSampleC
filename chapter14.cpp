#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

//Q1 实现拉链式冲突解决技术, 讨论每个函数时间复杂度

#define LOAD_FACTOR 20
struct ListNode
{
    int key;
    int data;
    struct ListNode *next;
};

struct HashTableNode
{
    int bcount; //链表中元素的个数
    struct ListNode *next;
};

struct HashTable
{
    int tsize;
    int count; //散列表中元素的个数
    struct HashTableNode **Table;
};

struct HashTable *CreateHashTable(int size)
{
    struct HashTable *h;
    h = (struct HashTable *)malloc(sizeof(struct HashTable));
    if (!h)
        return NULL;
    h->tsize = size / LOAD_FACTOR;
    h->count = 0;
    h->Table = (struct HashTableNode **)malloc(sizeof(struct HashTableNode *) * h->tsize);
    if (!h->Table)
    {
        printf("Memory Error");
        return NULL;
    }
    for (int i = 0; i < h->tsize; i++)
    {
        h->Table[i]->next = NULL;
        h->Table[i]->bcount = 0;
    }
    return h;
}

int HashSearch(struct HashTable *h, int data)
{
    struct ListNode *temp;
    temp = h->Table[Hash(data, h->tsize)]->next; //假设Hash是一个内置函数
    while (temp)
    {
        if (temp->data == data)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int HashInsert(struct HashTable *h, int data)
{
    int index;
    struct ListNode *temp, *newNode;
    if (HashSearch(h, data))
        return 0;
    index = Hash(data, h->tsize); //假设Hash是个内置函数
    temp = h->Table[index]->next;
    newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!newNode)
    {
        printf("Out of space");
        return -1;
    }
    newNode->key = index;
    newNode->data = data;
    newNode->next = h->Table[index]->next;
    h->Table[index]->next = newNode;
    h->Table[index]->bcount++;
    h->count++;
    if (h->count / h->tsize > LOAD_FACTOR)
        Rehash(h);
    return 1;
}

int HashDelete(struct HashTable *h, int data)
{
    int index;
    struct ListNode *temp, *prev;
    index = Hash(data, h->tsize);
    for (temp = h->Table[index]->next, prev = NULL; temp; prev = temp, temp = temp->next)
    {
        if (temp->data == data)
        {
            if (prev != NULL)
                prev->next = temp->next;
            free(temp);
            h->Table[index]->bcount--;
            h->count--;
            return 1;
        }
    }
    return 0;
}

void Rehash(struct HashTable *h)
{
    int oldsize, i, index;
    struct ListNode *p, *temp, *temp2;
    struct HashTableNode **oldTable;
    oldsize = h->tsize;
    oldTable = h->Table;
    h->tsize = h->tsize * 2;
    h->Table = (struct HashTableNode **)malloc(h->tsize * sizeof(struct HashTableNode *));
    if (!h->Table)
    {
        printf("Allocation Failed");
        return;
    }
    for (i = 0; i < oldsize; i++)
    {
        for (temp = oldTable[i]->next; temp; temp = temp->next)
        {
            index = Hash(temp->data, h->tsize);
            temp2 = temp;
            temp = temp->next;
            temp2->next = h->Table[index]->next;
            h->Table[index]->next = temp2;
        }
    }
}

//Q2 给定字符数组,给出一个删除重复字符的算法 时间复杂度O(n²) 空间复杂度O(1)
void RemoveDuplicates(char s[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n;)
        {
            if (s[i] == s[j])
                s[j] = s[--n];
            else
                j++;
        }
    }
    s[i] = '\0';
}

//Q3 改进Q2 利用排序算法将重复字符聚在一起,最后扫描数组删除连续位置重复字符

int Compare(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

void RemoveDuplicates(char s[])
{
    int last, current;
    QuickSort(s, strlen(s), sizeof(char), Compare);
    current = 0, last = 0;
    for (; s[current];)
    {
        if (s[last] != s[current])
            s[++last] = s[current];
    }
}

//Q4 在对给定数组仅一次的遍历过程解决这个问题
void RemoveDuplicates(char s[])
{
    int src, dst;
    struct HashTable *h;
    h = CreateHashTable();
    int current = 0, last = 0;
    for (; s[current]; current++)
    {
        if (!HashSearch(h, s[current]))
        {
            s[last++] = s[current];
            HashInsert(h, s[current]);
        }
    }
    s[last] = '\0';
}

//Q13 给出一个算法删除给定字符串由另一字符串指定字符?
//假设不同字符最大数量256,创建初始0的辅助数组,扫描需要删除的字符, 将对应数组设置为1 表示这个字符需要删除
//时间复杂度O(n)+(m) 空间复杂度O(m)
void RemoveChars(char str[], char RemoveTheseChars[])
{
    int srcInd, destInd;
    int auxi[256]; //辅助数组
    for (srcInd = 0; srcInd < 256; srcInd++)
        auxi[srcInd] = 0;
    //为所有需要删除的字符设置数组标识true
    srcInd = 0;
    while (RemoveTheseChars[srcInd])
    {
        auxi[RemoveTheseChars[srcInd]] = 1;
        srcInd++;
    }
    //复制字符,除非该字符必须删除
    srcInd = destInd = 0;
    while (str[srcInd++])
    {
        if (!auxi[str[srcInd]])
            str[destInd++] = str[srcInd];
    }
}

//Q14给出算法查找字符串的第一个非重复字符
//扫描剩余字符串,没出现就返回该字符 O(n²) O(1)
char FirstNonRepeatedChar(char *str)
{
    int i, j, repeated = 0;
    int len = strlen(str);
    for (i = 0; i < len; i++)
    {
        repeated = 0;
        for (j = 0; j < len; j++)
        {
            if (i != j && str[i] == str[j])
            {
                repeated = 1;
                break;
            }
        }
        if (repeated == 0) //找到第一个非重复字符
            return str[i];
    }
    return ' ';
}

//Q15 用散列表改善Q14
//O(n) + O(n) = O(2n)
char FirstNonRepeatedCharUsinghash(char *str)
{
    int i, len = strlen(str);
    int count[256]; //辅助数组
    for (i = 0; i < len; ++i)
        count[i] = 0;
    for (i = 0; i < len; ++i)
        count[str[i]]++;
    for (i = 0; i < len; ++i)
    {
        if (count[str[i]] == 1)
        {
            printf("%c", str[i]);
            break;
        }
    }
    if (i == len)
        printf("No Non-repeated Characters");
    return 0;
}

//Q16 找到字符串中第一个重复字母

char FirstRepeatedCharUsinghash(char *str)
{
    int i, len = strlen(str);
    int count[256]; //辅助数组
    for (i = 0; i < len; ++i)
        count[i] = 0;
    for (i = 0; i < len; ++i)
    {
        if (count[str[i]] == 1)
        {
            printf("%s", str[i]);
            break;
        }
        else
        {
            count[str[i]]++;
        }
    }
    if (i == len)
        printf("No repeated Characters");
    return 0;
}

//Q21 Bloom过滤器的实现

typedef unsigned int (*hashFunctionPointer)(const char *);
struct Bloom
{
    int bloomArraySize;
    unsigned char *bloomArray;
    int nHashFunctions;
    hashFunctionPointer *funcsArray;
};

#define SETBLOOMBIT(a, n) (a[n / CHAR_BIT] | = (1 << (n % CHAR_BIT)))
#define GETBLOOMBIT(a, n) (a[n / CHAR_BIT] | = (1 << (n % CHAR_BIT)))

struct Bloom *createBloom(int size, int nHashFunctions, ...)
{
    struct Bloom *blm;
    va_list l;
    int n;
    if (!(blm = (struct Bloom *)malloc(sizeof(struct Bloom *))))
        return NULL;
    if (!(blm->bloomArray = calloc((size + CHAR_BIT - 1) / CHAR_BIT, sizeof(char))))
    {
        free(blm);
        return NULL;
    }
    if (!(blm->funcsArray = (hashFunctionPointer *)malloc(nHashFunctions * sizeof(hashFunctionPointer))))
    {
        free(blm->bloomArray);
        free(blm);
        return NULL;
    }
    __va_start(&l, nHashFunctions);
    for (n = 0; n < nHashFunctions; ++n)
    {
        blm->funcsArray[n] = __crt_va_arg(l, hashFunctionPointer);
    }
    __crt_va_end(l);
    blm->nHashFunctions = nHashFunctions;
    blm->bloomArraySize = size;
    return blm;
}

int deleteBloom(struct Bloom *blm)
{
    free(blm->bloomArray);
    free(blm->funcsArray);
    free(blm);
    return 0;
}

int addElementBloom(struct Bloom *blm, const char *s)
{
    for (int n = 0; n < blm->nHashFunctions; ++n)
    {
        SETBLOOMBIT(blm->bloomArray, blm->funcsArray[n](s) % blm->bloomArraySize);
    }
    return 0;
}

int checkElementBloom(struct Bloom *blm, const char *s)
{
    for (int n = 0; n < blm->nHashFunctions; ++n)
    {
        if (!(GETBLOOMBIT(blm->bloomArray, blm->funcsArray[n](s) % blm->bloomArraySize)))
            return 0;
    }
    return 1;
}

unsigned int shiftAddXORHash(const char *key)
{
    unsigned int h = 0;
    while (*key)
        h ^= (h << 5) + (h >> 2) + (unsigned char)*key++;
    return h;
}

unsigned int XORHash(const char *key)
{
    unsigned int h = 0;
    hash_t h = 0;
    while (*key)
        h ^= *key++;
    return h;
}

int test()
{
    FLIE *fp;
    char line[1024];
    char *p;
    struct Bloom *blm;
    if (!(blm = createBloom(1500000, 2, shiftAddXORHash, XORHash)))
    {
        fprintf(stderr, "ERROR: Could not create Bloom filter\n");
        return -1;
    }
    if (!(fp = fopen("path", "r")))
    {
        fprintf(stderr, "ERROR:Could not open file %s\n", argv[1]);
        return -1;
    }
    while (fgets(line, 1024, fp))
    {
        if ((p = strchr(line, '\r')))
            *p = '\0';
        if ((p = strchr(line, '\n')))
            *p = '\0';
        addElementBloom(blm, line);
    }
    fclose(fp);
    while (fgets(line, 1024, stdin))
    {
        if ((p = strchr(line, '\r')))
            *p = '\0';
        if ((p = strchr(line, '\n')))
            *p = '\0';
        p = strtok(line, "\t,.;:\r\n?!-/()");
        while (p)
        {
            if (!checkElementBloom(blm, p))
            {
                printf("No match for ford \"%s\"\n", p);
            }
            p = strtok(NULL, "\t,.;:\r\n?!-/()");
        }
    }
    deleteBloom(blm);
    return 1;
}