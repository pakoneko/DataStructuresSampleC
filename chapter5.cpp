//队列变满进行EnQueue会造成满队列异常，变空进行DeQueue会造成空队列异常
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//基于简单循环数组实现队列
struct ArrayQueue {
    int front,rear;
    int capacity;
    int *array;
};

struct ArrayQueue *Queue(int size) {
    struct ArrayQueue *Q = (struct ArrayQueue *)malloc(sizeof(struct ArrayQueue));
    if(!Q)
        return NULL;
    Q->capacity = size;
    Q->front = Q->rear = -1;
    Q->array = (int *)malloc(Q->capacity * sizeof(int));
    if(!Q->array)
        return NULL;
    return Q;
}

int IsEmptyQueue(struct ArrayQueue *Q){
    return (Q->front == -1);
}

int IsFullQueue(struct ArrayQueue *Q) {
    return ((Q->rear + 1) % Q->capacity == Q->front);
}

int QueueSize(struct ArrayQueue *Q){
    return (Q->capacity - Q->front + Q->rear+1) % Q->capacity;
}

void EnQueue(struct ArrayQueue *Q, int data){
    if(IsFullQueue(Q)){
        printf("Queue Overflow");
    }
    else {
        Q->rear = (Q->rear + 1) % Q->capacity;
        Q->array(Q->rear) = data;
        if(Q->front == -1)
            Q->front = Q->rear;
    }
}

int DeQueue(struct ArrayQueue *Q){
    int data = 0;
    if(IsEmptyQueue(Q)) {
        printf("Queue is EMpty");
        return 0;
    }
    else {
        data =Q->array[Q->front];
            if(Q->front == Q->rear)
                Q->front = Q->rear = -1;
            else 
                Q->front = (Q->front+1) % Q->capacity;
    }
    return data;
}

void DeleteQueue(struct ArrayQueue *Q){
    if(Q) {
        if(Q->array)
            free(Q->array);
        free(Q);
    }
}

//基于链表实现队列

struct ListNode {
    int data;
    struct ListNode *next;
};

struct Queue {
    struct ListNode *front;
    struct ListNode *rear;
};

struct Queue *CreateQueue(){
    struct Queue *Q;
    struct ListNode *temp;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    if(!Q)
        return NULL;
    temp = (struct ListNode *)malloc(sizeof(struct ListNode));
    Q->front = Q->rear = NULL;
    return Q;
}

int IsEmptyQueue(struct Queue *Q){
    return (Q->front == NULL);
}

void EnQueue(struct Queue *Q, int data) {
    struct ListNode *newNode;
    newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if(!newNode)
        return;
    newNode->data = data;
    newNode->next = NULL;
    if(Q->rear)
        Q->rear->next = newNode;
    Q->rear = newNode;
    if(Q->front==NULL)
        Q->front = Q->rear; 
}

int DeQueue(struct Queue *Q){
    int data =0;
    struct ListNode *temp;
    if(IsEmptyQueue(Q)){
        printf("Queue is Empty");
        return 0;
    }
    else {
        temp = Q->front;
        data = Q->front->data;
        Q->front == Q->front->next;
        free(temp);
    }
    return data;
}

void DeleteQueue(struct Queue *Q) {
    struct ListNode *temp;
    while(Q){
        temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    free(Q);
}

//Q1 给一个算法完成对队列Q的转置

#pragma region Stack
struct Stack
{
    int top;
    int capacity;
    int *array;
};


int Top(struct Stack *S)
{
    /*S->top == -1 用来判断栈是否为空*/
    if (IsEmptyStack(S))
    {
        return INT_MIN;
    }
    return 0;
}

int IsEmptyStack(struct Stack *S)
{
    return (S->top == -1); //如果条件成立，则返回1，否则返回0
}

int IsFullStack(struct Stack *S)
{
    //如果条件成立，则返回1，否则返回0
    return (S->top == S->capacity - 1);
}

void Push(struct Stack *S, int data)
{
    /*S->top == capacity -1 用来判断栈是否已满 */
    if (IsFullStack(S))
        printf("Stack Overflow");
    else /*top增1，然后将元素存入top所指示的位置上*/
        S->array[++S->top] = data;
}

int Pop(struct Stack *S)
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
#define MAXSIZE 50;

struct Stack *CreateStack()
{
    struct Stack *S = (struct Stack *)malloc(sizeof(struct Stack));
    if (!S)
        return NULL;
    S->capacity = MAXSIZE;
    S->top = -1;
    S->array = (int *)malloc(S->capacity * sizeof(int));
    if (!S->array)
        return NULL;
    return S;
}
#pragma endregion

void ReversQueue(struct Queue *Q)
{
    struct Stack *S = CreateStack();
    while (!IsEmptyQueue(Q))
        Push(S, DeQueue(Q));
    while (!IsEmptyStack(S))
        EnQueue(Q, Pop(S));
};
//时间复杂度O(n)

//Q2 利用两个栈实现一个队列
//S1 S1两个用来实现队列的栈， 为队列定义入列操作和出列操作
struct Queue {
    struct Stack *S1; //实现EnQueue
    struct Stack *S2; //实现DeQueue
};

void EnQueue(struct  Queue *Q, int data)
{
    Push(Q->S1, data);
}


//时间复杂度O(1)

//出列如果栈S2不为空，那么从S2中弹出并返回栈顶元素
//如果栈S2为空，那么将S1中的所有元素移至S2中，然后从S2中弹出并返回栈顶元素

int DeQueue(struct Queue *Q) {
    if(!IsEmptyStack(Q->S2))
        return Pop(Q->S2);
    else {
        while(!IsEmptyStack(Q->S1))
            Push(Q->S2, Pop(Q->S1));
        return Pop(Q->S2);
    }
}
//Q3利用2个队列高效实现栈 必须确保其中一个队列始终为空
struct Stack {
    struct Queue *Q1;
    struct Queue *Q2;
};

//压入算法 将元素插入任意非空队列

//判断Q1是否为空，如果空则将元素插入Q2队尾 时间复杂度O(1)
void Push(struct Stack *S,int data) {
    if(IsEmptyQueue(S->Q1))
        EnQueue(S->Q2,data);
    else
        EnQueue(S->Q1,data);
}

//弹出：把非空队列的前n-1个元素移到另一个队列中，然后删除该队列最后一个元素完成弹出操作
//如果队列Q1非空，将Q1前n-1个元素移到Q2，然后对Q1实施 DeQueue操作删除并返回它最后一个元素
//如果队列Q2非空，那将Q2前n-1个元素移到Q1，然后对Q2实施 DeQueue操作删除并返回它最后一个元素
//时间复杂度O(n)

int Pop(struct Stack *S){
    int i, size;
    if(IsEmptyQueue(S->Q2)) {
        size =  sizeof(S->Q1);
        i=0;
        while(i<size-1){
            EnQueue(S->Q2,DeQueue(S->Q1));
            i++;
        }
        return DeQueue(S->Q1);
    }
    else {
        size = sizeof(S->Q2);
        while(i< size-1){
            EnQueue(S->Q1, DeQueue(S->Q2));
            i++;
        }
        return DeQueue(S->Q2);
    }
}

//Q4 滑动窗口中最大和问题：给定一个数组A[]和一个大小为w的滑动窗口。滑动窗口从数组的最左边向其最右边滑动
//假设我们只能看到位于窗口中的数组元素。
//滑动窗口每次向右移动一个位置，例如数组[1,3,-1,-3,5,3,6,7]和w为3的窗口。
//输入一个长数组A[]和一个大小为w的窗口，输出：数组B[]，其中B[i]是A[i]到A[i+w-1]的最大值，要求寻求最佳方法获得B[i]
//借助双端队列，参考第七章

//Q5 给定一个包含n个元素的队列Q，将元素转存到栈S。 需要O(n)算法。利用队列的EnQueue和DeQueue,和栈的Push ，Pop操作。使用常数个存储辅助单元
//把队列的元素a1~an 从队列删除压入栈，得到栈顶元素an和栈底元素a1的栈，然后再次把S元素全部Pop然后EnQueue去队列，就可以得到栈顶为a1的栈了。O(3n)≈O(n)

//Q6 队列用循环数组A[0...n-1]实现，队首(front) 队尾(rear)
//元素个数计算公式
//元素个数= {if rear ==front{rear-front+1} else {rear-front +n}}

//Q7 实现逆序打印队列元素最合适的数据结构是什么？
//栈

//Q8 双端队列可以在队首 队尾插入删除， 通常称为头-尾链表, 实现双端队列
struct ListNode{
    int data;
    struct ListNode *next,*prev;
};

void pushBackDEQ(struct ListNode **head, int data){
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    if(*head == NULL){
        *head = newNode;
        (*head)->next = *head; //next
        (*head)->prev = *head; //prev
    }
    else {
        newNode->prev = (*head)->prev;
        newNode->next = *head;
        (*head)->prev->next = newNode;
        (*head)->prev = newNode;
    }
}

void pushFrontDEQ(struct ListNode **head, int data){
    pushBackDEQ(head, data);
    *head=(*head)->prev;
}

int popBackDEQ(struct ListNode **head){
    int data;
    if((*head)->prev == *head){
        data  =(*head)->data;
        free(*head);
        *head = NULL;
    }
    else
    {
        struct ListNode *newTail = (*head)->prev->prev;
        data = (*head)->prev->data;
        newTail->next = *head;
        free((*head)->prev);
        (*head)->prev = newTail;
    }
    return data;    
}

int popFront(struct ListNode **head) {
    int data;
    *head = (*head)->next;
    data = popBackDEQ(head);
    return data;
}

//Q9 给定整数栈，判断相邻两元素构成的序对是否连续，连续的序对可以由递增2个元素或递减两个元素组成，如果栈包含奇数个元素，那么栈顶元素被排除在外。
//使用队列来解 时间复杂度 空间复杂度均为O(n)

int checkStackPairwiseOrder(struct Stack *s){
    struct Queue *q = CreateQueue();
    int pairewiseOrdered = 1;
    while(!IsEmptyStack(s))
        EnQueue(q, Pop(s)); //把栈中的元素依次压入队列
    while (!IsEmptyQueue(q))
        Push(s,DeQueue(q)); //把队列的元素再压回栈 实现了栈的翻转
    while (!IsEmptyStack(s))
    {
        int n = Pop(s); //获取栈弹出的元素
        EnQueue(q,n);   //压入队列
        if(!IsEmptyStack(s)){ //如果栈不为空
            int m = Pop(s); //获取弹出元素后面的一个元素
            EnQueue(q,m); //压入队列
            if(abs(n-m)!=1){ //相减不等于1的话 则不连续
                pairewiseOrdered = 0;
            }
        }
    }
    while(!IsEmptyQueue(q))
        Push(s,DeQueue(q));
    return pairewiseOrdered;
}

//Q10 整数队列，交叉存储序列前半部分元素和后半部分元素的方式重组其中的元素，假设用队列存储序列[11,12,13,14,15,16,17,18,19,20]
//前半部分[11,12,13,14,15]后半部分[16,17,18,19,20]交替组合[11,16,12,17,13,18,14,19,15,20]
// 时空复杂度O(n)

void interLeavingQueue(struct Queue *q){
    if(sizeof(q) %2!=0)
        return;
    struct  Stack *s = CreateStack();
    int halfSize = sizeof(q)/2;
    for (int i=0;i<halfSize; i++)
        Push(s, DeQueue(q));
    while(!IsEmptyStack(s))
        EnQueue(q,Pop(s));
    for(int i=0; i<halfSize;i++)
        EnQueue(q, DeQueue(q));
    for(int i=0;i<halfSize; i++)
        Push(s, DeQueue(q));
    while(!IsEmptyStack(s)){
        EnQueue(q, Pop(s));
        EnQueue(q, DeQueue(q));
    }    
}

//Q11 给一个整数k和一个整数队列，如何逆序队列的前k个元素同时保持其他元素的相对位置不变呢？例如 如果k=4， 队列[10,20,30,40,50,60,70,80,90]
//输出[40,30,20,10,50,60,70,80,90]
void reverseQueueFirstKElements(int k, struct Queue *q){
    if(q==NULL || k> sizeof(q)){
        return;
    }
    else if (k>0){
        struct Stack *s = CreateStack();
        for(int i=0; i<k;i++){
            Push(s, DeQueue(q)); //前k个提取到栈
        }
        while(!IsEmptyStack(s)){
            EnQueue(q, Pop(s)); //压回时候已逆置
        }
        for(int i=0; i<sizeof(q)-k;i++){
            EnQueue(q,DeQueue(q)); //再把后面几个重新取出来放回队尾
        }
    }
}