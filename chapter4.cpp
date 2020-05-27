//栈的抽象数据类型基于数组实现，从左向右的方向在数组中增加元素，并使用辅助变量跟踪栈顶元素在数组中的下标。
//数组变满进行push会抛出满栈异常，从空栈删除元素抛出空栈异常。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 10

struct ArrayStack
{
    int top;
    int capacity;
    int *array;
};

struct ArrayStack *CreateStack()
{
    struct ArrayStack *S = (struct ArrayStack *)malloc(sizeof(struct ArrayStack));
    if (!S)
        return NULL;
    S->capacity = MAXSIZE;
    S->top = -1;
    S->array = (int *)malloc(S->capacity * sizeof(int));
    if (!S->array)
        return NULL;
    return S;
}

int IsEmptyStack(struct ArrayStack *S)
{
    return (S->top == -1); //如果条件成立，则返回1，否则返回0
}

int IsFullStack(struct ArrayStack *S)
{
    //如果条件成立，则返回1，否则返回0
    return (S->top == S->capacity - 1);
}

void Push(struct ArrayStack *S, int data)
{
    /*S->top == capacity -1 用来判断栈是否已满 */
    if (IsFullStack(S))
        printf("Stack Overflow");
    else /*top增1，然后将元素存入top所指示的位置上*/
        S->array[++S->top] = data;
}

int Pop(struct ArrayStack *S)
{
    /*S->top == -1 用来判断栈是否为空*/
    if (IsEmptyStack(S))
    {
        printf("Stack is Empty");
        return 0;
    }
    else /*返回top所指位置上的元素（即栈顶元素），然后top减1*/
        return S->array[S->top--];
}

void DeleteStack(struct ArrayStack *S)
{
    if (S)
    {
        if (S->array)
            free(S->array);
        free(S);
    }
}

//Q5 在O(1)时间内实现Getminimum方法
//使用辅助栈

struct Stack
{
    int top;
    int capacity;
    int *array;
};

struct AdvancedStack
{
    struct Stack elementStack;
    struct Stack minStack;
};

int Top(struct AdvancedStack *S)
{
    /*S->top == -1 用来判断栈是否为空*/
    if (IsEmptyStack(S))
    {
        return INT_MIN;
    }
    return 0;
}

int IsEmptyStack(struct AdvancedStack *S)
{
    return (S->top == -1); //如果条件成立，则返回1，否则返回0
}

void Push(struct AdvancedStack *S, int data)
{
    Push(S->elementStack, data);
    if (IsEmptyStack(S->minStack) || Top(S->minStack) >= data)
        Push(S->minStack, data);
    else
        Push(S->minStack, Top(S->minStack));
}

int Pop(struct AdvancedStack *S)
{
    int temp;
    if (IsEmptyStack(S->elementStack))
        return -1;
    temp = Pop(S->elementStack);
    Pop(S->minStack);
    return temp;
}

int GetMinimum(struct AdvancedStack *S)
{
    return Top(S->minStack);
}

struct AdvancedStack *CreateAdvancedStack()
{
    struct AdvancedStack *S = (struct AdvancedStack *)malloc(sizeof(struct AdvancedStack));
    if (!S)
        return NULL;
    S->elementStack = CreateStack();
    S->minStack = CreateStack();
    return S;
}

//Q6提高 Q5的空间复杂度水准

void Push(struct AdvancedStack *S, int data)
{
    Push(S->elementStack, data);
    if (IsEmptyStack(S->minStack) || Top(S->minStack) >= data) //只有在压入主栈元素小于等于最小值，我们才对最小值栈做压入
        Push(S->minStack, data);
}

void Pop(struct AdvancedStack *S)
{
    int temp;
    if (IsEmptyStack(S->elementStack))
        return -1;
    temp = Top(S->elementStack); //只有主栈弹出元素等于最小栈的栈顶元素才从最小弹出元素
    if (Top(S->minStack) == Pop(S->elementStack))
    {
        Pop(S->minStack);
    }
    return temp;
}

//Q7 对于一个包含n个富豪的数组，有多少种可能的栈排列？
//用Catalan数来表示，见chapter19

//Q8给定字符数组仅有a字符，b字符组成的字符串，被X标记中间位置，(ababa...ababXbabab...baaa)判断是否回文。
//用下标变量指向串开头和末尾，每次比较2个下标变量所指位置上字符是否相同。，如果相同，左下标+1，右下标-1重复直到X处

int IsPalindrome(char *A)
{
    int i = 0, j = strlen(A) - 1;
    while (i < j && A[i] == A[j])
    {
        i++;
        j--;
    }
    if (i < j)
    {
        printf("Not a Palindrome");
        return 0;
    }
    else
    {
        printf("Palindrome");
        return 1;
    }
}

//Q9 针对Q8如果输出串是单链表表示的呢（无法向后移动)如何判断 查看chapter3 Q37

//Q10 利用栈来解答Q8
//遍历字符串直到遇到X作为输入元素
//遍历的时候把所有遇到的字符压入栈
//对输入字符串的后半部分，比较当前位置上字符与栈顶字符是否相同
//不同就不是回文，重复直到不是回文或者栈为空
int IsPalindrome(char *A)
{
    int i = 0;
    struct Stack S = CreateStack();
    while (A[i] != 'X')
    {
        Push(S, A[i]);
        i++;
    }
    i++;
    while (A[i])
    {
        if (IsEmptyStack(S) || A[i] != Pop(S))
        { //如果A后半段的长度大于栈内长度，说明也不是回文
            printf("Not a Palindrome");
            return 0;
        }
        i++;
    }
    return IsEmptyStack(S);
}

//Q11 给定一个栈，如何仅用栈的Push和Pop操作实现栈的倒置？

//首先POP出所有元素直到它变空，
//递归中的每次返回步骤插入一个元素到栈底。

//下面是一个递归函数，在栈的底部插入一个元素 //时间复杂度O(n²) 空间复杂度O(n)
void ReverseStack(struct Stack *S)
{
    int data;
    if (IsEmptyStack(S))
        return;
    data = Pop(S);
    ReverseStack(S);
    InsertAtBottom(S, data);
}

//下面是一个递归函数，在栈的底部插入一个元素
void InsertAtBottom(struct Stack *s, int data)
{
    int temp;
    if (IsEmptyStack(S))
    {
        Push(S, data);
        return;
    }
    /*保存函数调用的栈中的所有项，直到到达栈的末端。
    当栈变为空时，IsEmptyStack(S)变为真，上面的“if”部分将被执行，并将项插入底部
    */
    temp = Pop(S);
    InsertAtBottom(S, data);
    //一旦将项插入到底部，就Push函数调用栈中包含的所有项
    Push(S, temp);
}

//Q12 2个栈高效实现队列的方法，分析队列操作的时间开销
//Q13 2个队列高效实现栈的方法，分析栈操作的时间开销
//以上参考chapter5
//Q14 仅仅用一个数组实现2个栈，保证栈基本操作不会发生异常，除非数组所有位置均已使用

/* 开始一个下标变量指向数组的左端，另一个下标变量指向数组的右端
左下标变量模拟第一个栈，右下标变量模拟第二个栈
压入一个元素到第一个栈的时候把它压入左下标变量所指示位置，压入一个元素到第二个栈将元素压入右下标变量所指示位置
第一个栈向右生长，第二个栈向左生长。时间复杂度O(1)，空间复杂度O(1)
*/
//Q15 一个数组包含3个栈 怎么实现？
//先保存第一个栈的下标Top1，第二个栈的下标Top2，第三个栈的开始下标Top3
//PUSH的时候判断新增元素是否发生碰撞，如果会，将第三个栈向上移动，然后新元素插入start+top1位置
//第二个栈的压入，判断新增会不会与第三个栈碰撞，如果会，将第三个栈向下移动，新元素插入start2+Top2指示位置
//第三个栈的压入，判断新增元素是否会导致它与第二个栈发生碰撞，如果会，将先尝试向下移动，然后尝试压入元素，最后插入start3+Top3所指示位置

//Q16其他实现方式 优化位置，来减少中间栈的移动次数

//Q17 一个数组含m个栈，如何实现。

//把栈划分为m个部分，每个部分大小n/m

void Push(int StackID, int data)
{
    if (Top[i] == Base[i + 1])
    {
        //打印输出第i个栈满了， 并进行其他需要完成的操作（移动）
    }
    Top[i] = Top[i] + 1;
    A[Top[i]] = data; //A代表数组
}

//时间复杂度O(n),空间复杂度O(1)

//弹出第i个栈

int Pop(int StackID)
{
    if (Top[i] == Base[i])
    {
        //输出第i个栈空了
    }
    return A[Top[i]--];
}

//Q22 求解元素的跨度：给定数组A，A[i]的跨度S[i]是指，挨着A[i]且位于A[i]之前连续满足A[j]<=A[i]条件的元素A[j]的个数。
//给定一个整数数组A，找到满足A[i]<A[i]条件下的最大j-i的值
//股票峰值，跨度金融分析，股票价格在某天i的跨度指股票价格小于等于第i天股票价格的持续天数最大值。

FindingSpans(int A[], int n)
{
    int i, j, S[n]; //大小为n的新整型数组
    for (i = 0; i < n; i++)
    {
        j = 1;
        while (j <= i && A[i] > A[i - j])
            j = j + 1;
        S[i] = j;
    }
    return S;
}

//时间复杂度O(n²)空间复杂度O(1)

//Q23提高Q22的时间复杂度水准
//数组每个下标压入栈一次，最多弹出栈一次，while循环最多执行n次，虽然有嵌套循环 ，时间复杂度为O(n),因为内层循环最多n次

FindingSpans(int A[], int n)
{
    struct Stack *D = CreateStack();
    int P;
    for (int i = 0; i < n; i++)
    {
        while (!IsEmptyStack(D) && A[i] > [Top(D)])
        {
            Pop(D);
        }
        if (IsEmptyStack(D))
            P = -1;
        else
            P = Top(D);
        S[i] = i - P; //P为第i天之前距离第i天最近且其股票价格高于第i天的股票价格那一天，如果P存在则执行这句
        Push(D, i);
    }
    return S;
}

//Q24 直方图中的最大矩形
//直接方法，对直方图每个参观条找出可能最大区域，在这些区域找出最大值，时间开销O(n²)
//Q25 提高时间复杂度水平
//利用栈对不完全子问题线性搜索。每个循环元素每一次只进行1次入栈出栈操作，所以时间开销O(n)
////当前元素大于栈顶元素的时候，将当前元素压入栈 如果当前比栈顶元素小，就计算栈顶元素最高高度的子直方图最大矩形面积
//如果计算结果大于当前找到最大矩形面积，就更新计算结果到最大举行面积，弹出栈顶
struct StackItem
{
    int height;
    int index;
};

int MaxRectangleArea(int A[], int n)
{
    int i, maxArea = -1, top = -1, left, currentArea;
    struct StackItem *S = (struct StackItem *)malloc(sizeof(struct StackItem) * n);
    for (i = 0; i <= n; i++)
    {
        while (top >= 0 && (i == n || S[top]->height > A[i]))
        {
            if (top > 0)
                left = S[top - 1]->index;
            else
                left = -1;
            currentArea = (i - left - 1) * S[top]->height;
            --top;
            if (currentArea > maxArea)
                maxArea = currentArea;
        }
        if (i < n)
        {
            ++top;
            S[top]->height = A[i];
            S[top]->index = i;
        }
    }
    return maxArea;
}

//Q26 给定的机器上如何判定栈向上生长还是向下生长？
//记录下一个局部变量地址，调用另一个函数，声明一个局部变量，考察内存地址并比较。

int testStackGrowth()
{
    int temporary;
    stackGrowth(&temporary);
    exit(0);
}

void StackGrowth(int *temp)
{
    int temp2;
    printf("\nAddress of first local valuable:%u", temp);
    printf("\nAddress of second local:%u", &temp2);
    if (temp < &temp2)
        printf("\n Stack is growing downwards");
    else
    {
        printf("\n Stack is growing upwards");
    }
}

//Q27 给一个整数栈，如何判断相邻元素构成整数对是否连续数字
//参考第五章

//Q28 删除所有相邻副本，给定一个字符串删除所有重复出现且相邻字符
//输入careermonk 输出camonk 输入mississippi 输出m
// 当栈顶元素与当前字符不匹配，将当前字符压入栈，匹配时就跳过继续向后扫描直到不匹配，最后弹出栈顶元素 时间复杂度O(n) ,空间复杂度O(1)
void removeAdjacentDuplicates(char *str)
{
    int stkptr = -1;
    int i = 0;
    int len = strlen(str);
    while (i < len)
    {
        if (stkptr == -1 || str[stkptr] != str[i])
        {
            stkptr++;
            str[stkptr] = str[i];
            i++;
        }
        else
        {
            while (i < len && str[stkptr] == str[i])
                i++;
            stkptr--;
        }
    }
    str[stkptr + 1] = '\0';
}

//Q29 给一个数组，对数组中每个元素，用该元素右边最接近它且比它大的元素替换该元素

//简单方法扫描数组的元素
void replaceWithNearestGreaterElement(int A[], int n)
{
    int nextNearestGreater = INT_MIN;
    int i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        nextNearestGreater = -INT_MIN;
        for (j = i + 1; j < n; j++)
        {
            if (A[i] < A[j])
            {
                nextNearestGreater = A[j];
                break;
            }
        }
    }
    printf("For the element %d, %d is the nearest greater element\n", A[i], nextNearestGreater); //时间复杂度O(n²) 空间复杂度O(1)
}

//Q30 提高Q29算法时间复杂度水平 创建一个栈 将第一个元素压入栈，对剩下的元素，将当前元素标记为nextNearestGreater，如果栈非空则弹出栈顶元素，将其与nextNearestGreater比较，如果nextNearestGreater>弹出元素
//那么nextNearestGreater就是弹出元素的最近更大元素，如果弹出元素<nextNearestGreater则持续弹出元素，nextNearestGreater是所有弹出元素的最近更大元素，如果nextNearestGreater<弹出元素，将弹出元素压回栈

void replaceWithNearestGreaterElement(int A[], int n)
{
    int i = 0;
    struct Stack *S = CreateStack();
    int element, nextNearestGreater;
    Push(S,A[0]);
    for(i=1;i<n;i++){
        nextNearestGreater = A[i];
        if(!IsEmptyStack(S)){
            element=Pop(S);
            while(element<nextNearestGreater){
                printf("For the element %d, %d is the nearest greater element\n", A[i], nextNearestGreater); //时间复杂度O(n) 空间复杂度O(n)
                if(IsEmptyStack(S))
                    break;
                element = Pop(S);
            }
            if(element>nextNearestGreater)
                Push(S,element);
        }
        Push(S,nextNearestGreater);
    }
    /*遍历循环之后，剩下的
堆栈中的元素没有下一个更大的元素，因此为它们打印-1 */
    while(!IsEmptyStack(S)){
        element = Pop(S);
        nextNearestGreater = -INT_MIN;
        printf("For the element %d, %d is the nearest greater element\n", A[i], nextNearestGreater);
    }
}

//Q31 如何实现一个栈，用O(1)时间复杂度支持以下操作
//在栈的顶部添加一个元素
//在栈的顶部弹出一个元素
//查找栈中间的元素并返回
//删除栈中间的元素

//我们可以使用链表和一个额外的指针指向中点，并且需要一个变量保存链表是否拥有奇数或者偶数
//新增元素的时候更新中点指针
//删除元素的时候更新中点指针
//返回中点指针位置
//删除中点 使用chapter3的Q43的解答的逻辑